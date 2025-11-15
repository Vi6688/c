#pragma once
#include "BasicTypes.h"

typedef enum { LOW = 0, MID = 1, HIGH = 2 } Priority;

typedef enum {
  NO_ERROR = 0, // No error
  INVALID_ID,   // Process ID is invalid
  QUEUE_FULL,   // Cannot add process to queue
  QUEUE_EMPTY,  // Cannot remove process from queue
  FAILED,       // function returned with an error
  MEMORY_ERROR, // Allocation failed
  TIMEOUT
} Error;

typedef enum {
  NEW = 0,   // Process just created
  READY,     // Waiting in queue
  RUNNING,   // Currently executing
  WAITING,   // Waiting for I/O or resource
  TERMINATED // Finished execution
} Status;

typedef struct {
  Time start;
  Time end;
  Time timeTaken;
  Status status;
  Error error;
} *ProcessDetails;

typedef struct {
  int id;
  Priority priority;
  string name;
  ProcessDetails details;
  Boolean loop;
  void *args;
  int (*func)(void *args);
} *Process;

void runTasks();
Boolean scheduleTask(string name, int (*func)(void *args), void *args,
                     Priority priority, Boolean loop);