#include "Scheduler.h"
#include "BasicTypes.h"
#include "List.h"
#include "Memory.h"
#include "Mutex.h"
#include "Thread.h"
#include "Time.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

static int id_counter = 0;
static Boolean initialized = false;
static List highPriorityProcesses = NULL;
static List midPriorityProcesses = NULL;
static List lowPriorityProcesses = NULL;
static Mutex mutex = NULL;
static size_t sizeOfProcess = sizeof(*((Process)0));
static size_t sizeOfProcessDetails = sizeof(*((ProcessDetails)0));

static void initialise(void) {
  if (initialized)
    return;
  mutex = createMutex();

  highPriorityProcesses = createList(sizeof(Process));
  midPriorityProcesses = createList(sizeof(Process));
  lowPriorityProcesses = createList(sizeof(Process));

  initialized = true;
}

int sleepTime(Priority priority) {
  switch (priority) {
  case HIGH:
    return 1000;
  case MID:
    return 500;
  case LOW:
    return 5000;
  default:
    return 100;
  }
}

Boolean scheduleTask(string name, int (*func)(void *args), void *args,
                     Priority priority, Boolean loop) {
  if (!initialized)
    initialise();

  lock(mutex);

  Process newProc = (Process)newAlloc(sizeOfProcess);
  if (!newProc) {
    unlock(mutex);
    return false;
  }
  newProc->details = (ProcessDetails)newAlloc(sizeOfProcessDetails);
  if (!newProc->details) {
    free(newProc);
    unlock(mutex);
    return false;
  }

  newProc->id = id_counter++;
  newProc->priority = priority;
  newProc->loop = loop;
  newProc->func = func;
  newProc->args = args;

  newProc->name = (string)newAlloc(strlen(name) + 1);
  strcpy(newProc->name, name);

  newProc->details->start = currentTime();
  newProc->details->status = NEW;
  newProc->details->error = NO_ERROR;

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

DWORD WINAPI executeProcess(voidPtr args) {
  if (!args)
    return 1;
  Process process = (Process)args;
  if (!process->func)
    return 1;

  ProcessDetails details = process->details;
  if (details)
    details->status = RUNNING;

  int result = process->func(process->args);

  if (details) {
    details->end = currentTime();
    details->timeTaken = details->end - details->start;
    details->status = TERMINATED;
    details->error = (result == 0) ? NO_ERROR : FAILED;
  }

  return (DWORD)result;
}

DWORD WINAPI runTasks(voidPtr args) {
  (void)args;
  printf("Scheduler started...\n");

  if (!initialized)
    initialise();

  while (true) {
    lock(mutex);

    List priorityLists[] = {highPriorityProcesses, midPriorityProcesses,
                            lowPriorityProcesses};
    Boolean executed = false;

    for (int i = 0; i < 3; ++i) {
      List list = priorityLists[i];
      if (list && list->size > 0) {
        Process process = *(Process *)valueAt(list, 0);
        unlock(mutex);
        executeProcess(process);
        if (process->loop) {
          deleteElement(list, 0);
          appendList(list, &process);
        } else {
          deleteElement(list, 0);

          if (process->name)
            freeAlloc(process->name);
          if (process->details)
            freeAlloc(process->details);
          freeAlloc(process);
        }
        lock(mutex);

        executed = true;
        break;
      }
    }

    if (!executed) {
      unlock(mutex);
      Sleep(10);
    } else {
      unlock(mutex);
    }
  }

  return 0;
}
