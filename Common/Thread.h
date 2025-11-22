#pragma once
#include "BasicTypes.h"
#include "List.h"
#include "Memory.h"
#include <Windows.h>

int createThread(DWORD(WINAPI *threadFunc)(LPVOID), void *args);
int createAndJoin(DWORD(WINAPI *threadFunc)(LPVOID), void *args);
int joinThread(int thread);
int stopThread(int thread);
int resumeThread(int thread);
Boolean destructThread(int thread);
void destructThreads(void);
void destroyAllThreads(void);    
