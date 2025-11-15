#pragma once
#include "BasicTypes.h"
#include "List.h"
#include "Memory.h"
#include <Windows.h>


int createThread(DWORD (WINAPI *func)(LPVOID), void *args);
int createAndJoin(DWORD (WINAPI *func)(LPVOID), void *args);
int joinThread(int thread);
Boolean destructThread(int thread);
void destructThreadHandles();