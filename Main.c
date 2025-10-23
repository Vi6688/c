#include <windows.h>
#include <stdio.h>

DWORD WINAPI run_thread(LPVOID arg) {
    printf("Running thread...\n");
    return 0;
}

int main() {
    HANDLE h = CreateThread(NULL, 0, run_thread, NULL, 0, NULL);
    WaitForSingleObject(h, INFINITE);
    CloseHandle(h);
    return 0;
}
