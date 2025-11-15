#include "Scheduler.h"
#include "BasicTypes.h"
#include "List.h"
#include "Memory.h"
#include "Mutex.h"
#include "Time.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

static int id = 0;
static Boolean init = false;
static List highPriorityProcesses;
static List midPriorityProcesses;
static List lowPriorityProcesses;
static Mutex mutex;
static size_t sizeOfProcess = sizeof(*((Process)0));
static size_t sizeOfProcessDetails = sizeof(*((ProcessDetails)0));

void initialise() {
  mutex = createMutex();

  highPriorityProcesses = createList(sizeof(Process));
  midPriorityProcesses  = createList(sizeof(Process));
  lowPriorityProcesses  = createList(sizeof(Process));

  init = true;
}

Boolean scheduleTask(string name, int (*func)(void *args), void *args,
                     Priority priority, Boolean loop) {
  if (!init)
    initialise();

  lock(mutex);

  // Allocate a new Process and its details
  Process newProc = (Process)newAlloc(sizeOfProcess);
  newProc->details = (ProcessDetails)newAlloc(sizeOfProcessDetails);

  // Assign metadata
  newProc->id = id++;
  newProc->priority = priority;
  newProc->loop = loop;
  newProc->func = func;
  newProc->args = args;

  // Duplicate or assign name safely
  newProc->name = (string)newAlloc(strlen(name) + 1);
  strcpy(newProc->name, name);

  // Initialize details
  newProc->details->start = currentTime();
  newProc->details->status = NEW;
  newProc->details->error = NO_ERROR;

  // Append based on priority
  switch (priority) {
  case HIGH:
    appendList(highPriorityProcesses, &newProc);
    break;
  case MID:
    appendList(midPriorityProcesses, &newProc);
    break;
  case LOW:
    appendList(lowPriorityProcesses, &newProc);
    break;
  default:
    unlock(mutex);
    return false;
  }

  unlock(mutex);
  return true;
}

void executeProcess(Process process) {
  if (!process || !process->func)
    return;

  ProcessDetails details = process->details;
  details->status = RUNNING;

  // Run the task
  int result = process->func(process->args);

  if (result != 0) {
    details->error = NO_ERROR;
  } else {
    details->error = FAILED;
  }

  details->end = currentTime();
  details->timeTaken = details->end - details->start;
  details->status = TERMINATED;
}

void runTasks() {
  while (true) {
    lock(mutex);

    List priorityLists[] = {
        highPriorityProcesses,
        midPriorityProcesses,
        lowPriorityProcesses};

    Boolean executed = false;

    for (int i = 0; i < 3; i++) {
      List list = priorityLists[i];
      if (list && list->size > 0) {
        Process process = *(Process *)valueAt(list, 0);

        unlock(mutex); // release before running task
        executeProcess(process);
        lock(mutex);   // re-lock before modifying list

        if (process->loop) {
          appendList(list, &process); // re-queue
        } else {
          deleteElement(list, 0);
          free(process->name);
          free(process->details);
          free(process);
        }

        executed = true;
        break;
      }
    }

    unlock(mutex);

    if (!executed) {
      Sleep(10); // yield CPU if no tasks
    }
  }
}
