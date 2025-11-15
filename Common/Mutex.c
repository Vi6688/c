#include "BasicTypes.h"
#include <Windows.h>
#include "Mutex.h"

void lock(Mutex mutex) { WaitForSingleObject(mutex, INFINITE); }

Mutex createMutex() { return CreateMutex(NULL, FALSE, NULL); }

void unlock(Mutex mutex) { ReleaseMutex(mutex); }