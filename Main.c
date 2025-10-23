#include <stdio.h>
#include <windows.h>
#include "Thread.h"

DWORD WINAPI run_thread(LPVOID arg) {
    int id = *(int*)arg;
    printf("Thread %d running...\n", id);
    Sleep(1000);
    printf("Thread %d done.\n", id);
    return 0;
}

int main() {
    int p1 = 1, p2 = 2, p3 = 3;

    createAndJoin(run_thread, &p1);
    createThread(run_thread, &p2);
    createThread(run_thread, &p3);

    joinThread(1);
    joinThread(2);

    destruct();
}
