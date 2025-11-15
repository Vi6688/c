#include "BasicTypes.h"
#include "Memory.h"
#include "Scheduler.h"
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

int backgroundLogger(void *args) {
  string name = (string)args;
  printf("[Logger] %s writing logs...\n", name);
  Sleep(500);
  return 1;
}

// -----------------------------------------------------
// Main
// -----------------------------------------------------

int main(void) {
  printf("===== Scheduler Demo Started =====\n");

  // Create and schedule a bunch of tasks
  scheduleTask("CPU_1", cpuIntensiveTask, "CPU_1", HIGH, false);
  scheduleTask("CPU_2", cpuIntensiveTask, "CPU_2", HIGH, false);
  scheduleTask("IO_1", ioTask, "IO_1", MID, false);
  scheduleTask("IO_2", ioTask, "IO_2", MID, false);
  scheduleTask("Sensor_1", periodicSensorTask, "Sensor_1", LOW, true);
  scheduleTask("Sensor_2", periodicSensorTask, "Sensor_2", LOW, true);
  scheduleTask("Logger_1", backgroundLogger, "Logger_1", LOW, true);
  scheduleTask("Logger_2", backgroundLogger, "Logger_2", LOW, true);

  printf("===== Scheduler Demo Started =====\n");

  // Run all tasks forever (like a tiny RTOS loop)
  runTasks();
  destruct();
  return 0;
}

