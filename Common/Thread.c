#include "Thread.h"
#include "BasicTypes.h"
#include "List.h"
#include <stdio.h>
#include <windows.h>

List threads = NULL; // Initialize to NULL

int createThread(DWORD(WINAPI *func)(LPVOID), void *args) {
    if (!threads) {
        threads = createList(sizeof(HANDLE));
    }

    HANDLE h = CreateThread(NULL, 0, func, args, 0, NULL);
    if (!h)
        return -1;

    appendList(threads, &h); // Correct: store HANDLE value (not pointer to local)
    return (int)(threads->size - 1);
}

int createAndJoin(DWORD(WINAPI *func)(LPVOID), void *args) {
    int thread = createThread(func, args);
    if (thread >= 0) {
        joinThread(thread);
    }
    return thread;
}

int joinThread(int thread) {
    if (!threads || thread >= threads->size) {
        return 0;
    }

    HANDLE *handleArray = (HANDLE *)threads->data;
    HANDLE h = handleArray[thread];

    WaitForSingleObject(h, INFINITE);
    return 1;
}

Boolean destructThread(int thread) {
    if (!threads || thread >= threads->size) {
        return false;
    }

    HANDLE *handleArray = (HANDLE *)threads->data;
    CloseHandle(handleArray[thread]);
    deleteElement(threads, thread); // shifts list memory
    return true;
}

void destructThreadHandles() {
    if (!threads || !threads->size) return;

    HANDLE *handleArray = (HANDLE *)threads->data;
    for (size_t i = 0; i < threads->size; i++) {
        CloseHandle(handleArray[i]);
    }
}
