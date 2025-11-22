#include "Thread.h"
#include "List.h"     
#include <windows.h>
#include <stdio.h>
#include "BasicTypes.h"

/*
 * Implementation notes:
 * - The List stores elements of type HANDLE (size = sizeof(HANDLE)).
 * - appendList(list, &h) appends the HANDLE value; valueAt(list, idx) returns pointer to the stored HANDLE.
 * - deleteElement(list, idx) removes that element and shifts elements; per your note it also frees internal memory.
 * - threadId is the index into the List (0 .. size-1). After destroyThread(threadId) that index no longer refers to the same thread.
 */

/* Static single list for thread handles */
static List threads = NULL;

/* Create a new thread and append its HANDLE to the threads list.
 * Returns: index (0..n-1) on success, -1 on failure.
 */
int createThread(DWORD(WINAPI *threadFunc)(LPVOID), void *args)
{
    if (!threadFunc) return -1;

    if (!threads) {
        threads = createList(sizeof(HANDLE));
        if (!threads) return -1;
    }

    HANDLE h = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadFunc, args, 0, NULL);
    if (!h) {
        return -1;
    }

    /* Append the HANDLE value to the list. appendList expects pointer to data. */
    appendList(threads, &h);

    /* thread index is last element's index (size - 1) */
    return (int)(threads->size - 1);
}

/* Wait for the thread to finish.
 * Returns non-zero on success, zero on failure.
 * Does NOT remove the element from the list; use destroyThread() to close/remove.
 */
int joinThread(int threadId)
{
    if (!threads) return 0;
    if (threadId < 0 || (size_t)threadId >= threads->size) return 0;

    HANDLE *hptr = (HANDLE *)valueAt(threads, (size_t)threadId);
    if (!hptr || *hptr == NULL) return 0;

    DWORD wait = WaitForSingleObject(*hptr, INFINITE);
    return (wait == WAIT_OBJECT_0);
}

/* Suspend the thread (SuspendThread). Returns non-zero on success. */
int stopThread(int threadId)
{
    if (!threads) return 0;
    if (threadId < 0 || (size_t)threadId >= threads->size) return 0;

    HANDLE *hptr = (HANDLE *)valueAt(threads, (size_t)threadId);
    if (!hptr || *hptr == NULL) return 0;

    DWORD prev = SuspendThread(*hptr);
    return (prev != (DWORD)-1);
}

/* Resume the thread (ResumeThread). Returns non-zero on success. */
int resumeThread(int threadId)
{
    if (!threads) return 0;
    if (threadId < 0 || (size_t)threadId >= threads->size) return 0;

    HANDLE *hptr = (HANDLE *)valueAt(threads, (size_t)threadId);
    if (!hptr || *hptr == NULL) return 0;

    DWORD prev = ResumeThread(*hptr);
    return (prev != (DWORD)-1);
}

/* Close handle and remove the element from the list.
 * Returns true on success, false on failure.
 */
Boolean destroyThread(int threadId)
{
    if (!threads) return false;
    if (threadId < 0 || (size_t)threadId >= threads->size) return false;

    HANDLE *hptr = (HANDLE *)valueAt(threads, (size_t)threadId);
    if (hptr && *hptr) {
        CloseHandle(*hptr);
    }
    deleteElement(threads, (size_t)threadId);
    return true;
}

void destroyAllThreads(void)
{
    if (!threads) return;

    if (threads->size == 0) return;
    HANDLE *arr = (HANDLE *)threads->data;
    for (size_t i = 0; i < threads->size; ++i) {
        if (arr[i]) {
            CloseHandle(arr[i]);
            arr[i] = NULL;
        }
    }
}
