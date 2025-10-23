#include "Thread.h"
#include <windows.h>

ListPtr threads;

int createThread(DWORD(WINAPI *func)(LPVOID), void *args) {
    if (!threads) {
        threads = createList(sizeof(HANDLE));
    }

    HANDLE h = CreateThread(NULL, 0, func, args, 0, NULL);
    if (!h) return -1;

    appendList(threads, &h); // Pass address
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

void destructThreadHandles() {
    if (!threads || !threads->size) {
        return;
    }

    HANDLE *handleArray = (HANDLE *)threads->data;
    for (size_t i = 0; i < threads->size; i++) {
        CloseHandle(handleArray[i]);
    }
}
