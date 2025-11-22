#include "BasicTypes.h"
#include "Memory.h"
#include "Scheduler.h"
#include "Thread.h"
#include <stdio.h>
#include <windows.h>

int cpuIntensiveTask(void *args) {
  string name = (string)args;
  printf("[CPU] Task %s started\n", name);

  double sum = 0;
  for (long long i = 0; i < 50000000; ++i) { // heavy loop
    sum += (i % 3) * 0.33;
  }

  printf("[CPU] Task %s finished (sum=%.2lf)\n", name, sum);
  return 1;
}

int ioTask(void *args) {
  string name = (string)args;
  printf("[I/O] Task %s started\n", name);

  for (int i = 0; i < 3; ++i) {
    printf("[I/O] %s reading chunk %d...\n", name, i + 1);
    Sleep(300); // simulate I/O wait
  }

  printf("[I/O] Task %s completed\n", name);
  return 1;
}

int periodicSensorTask(void *args) {
  string name = (string)args;
  static int count = 0;

  printf("[Sensor] Task %s iteration %d\n", name, ++count);
  Sleep(200);
  return (count < 5); // run only 5 times (non-looping)
}

/**
 * @brief Background logger task that runs indefinitely
 * 
 * @param args Task name
 * @return int - if successful returns 1
 */
int backgroundLogger(void *args) {
  string name = (string)args;
  printf("[Logger1] %s writing logs...\n", name);
  Sleep(500);
  return 1;
}
int backgroundLogger2(void *args) {
  string name = (string)args;
  printf("[Logger2] %s writing logs...\n", name);
  Sleep(700);
  return 1;
}

int main(void) {

  // Create and schedule a bunch of tasks
  scheduleTask("CPU_1", cpuIntensiveTask, "CPU_1", HIGH, false);//TODO fix the scheduler after removing the threading model
  scheduleTask("CPU_2", cpuIntensiveTask, "CPU_2", HIGH, false);
  scheduleTask("IO_1", ioTask, "IO_1", MID, false);
  scheduleTask("IO_2", ioTask, "IO_2", MID, false);
  scheduleTask("Sensor_1", periodicSensorTask, "Sensor_1", LOW, false);
  scheduleTask("Sensor_2", periodicSensorTask, "Sensor_2", LOW, false);
  scheduleTask("Logger_1", backgroundLogger, "Logger_1", LOW, false);
  scheduleTask("Logger_2", backgroundLogger, "Logger_2", LOW, false);
  scheduleTask("Logger_3", backgroundLogger2, "Logger_3", LOW, false  );

  printf("===== Scheduler Demo Started =====\n");

  int threadId = createThread(runTasks, NULL);
  joinThread(threadId);
  destruct();
  return 0;
}

