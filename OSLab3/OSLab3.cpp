#include "OSLab3.h"

int array_size = 0;
int* arr = nullptr;
CRITICAL_SECTION cs;

DWORD WINAPI marker(LPVOID thread_index) {
    WaitForSingleObject(hThreadsStartEvents[(int)thread_index], INFINITE);
    int marked_numbers_counter = 0;
    srand((int)thread_index);

    while (true) {
        int random_number = rand() % array_size;
        if (arr[random_number] == 0) {
            EnterCriticalSection(&cs);
            Sleep(5);
            arr[random_number] = (int)thread_index + 1;
            marked_numbers_counter++;
            Sleep(5);
            LeaveCriticalSection(&cs);
        }
        else {
            EnterCriticalSection(&cs);
            std::cout << "\nThread #" << (int)thread_index
                << "\nMarked Elements: " << marked_numbers_counter
                << "\nFailed Index: " << random_number << "\n";
            LeaveCriticalSection(&cs);
            break;
        }
    }
    return 0;
}

void initializeThreads(int amount_of_threads, HANDLE*& hThreads, HANDLE*& hThreadsStartEvents, HANDLE*& hThreadWorkStopped, HANDLE*& hThreadsExit, DWORD*& dwThreads) {
    hThreads = new HANDLE[amount_of_threads];
    hThreadsStartEvents = new HANDLE[amount_of_threads];
    hThreadWorkStopped = new HANDLE[amount_of_threads];
    hThreadsExit = new HANDLE[amount_of_threads];
    dwThreads = new DWORD[amount_of_threads];

    for (int i = 0; i < amount_of_threads; ++i) {
        hThreads[i] = CreateThread(NULL, 0, marker, (LPVOID)i, 0, &dwThreads[i]);
        hThreadsStartEvents[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
        hThreadWorkStopped[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
        hThreadsExit[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
    }
}

void cleanupThreads(int amount_of_threads, HANDLE*& hThreads, HANDLE*& hThreadsStartEvents, HANDLE*& hThreadWorkStopped, HANDLE*& hThreadsExit) {
    for (int i = 0; i < amount_of_threads; ++i) {
        CloseHandle(hThreads[i]);
        CloseHandle(hThreadsStartEvents[i]);
        CloseHandle(hThreadWorkStopped[i]);
        CloseHandle(hThreadsExit[i]);
    }

    delete[] hThreads;
    delete[] hThreadsStartEvents;
    delete[] hThreadWorkStopped;
    delete[] hThreadsExit;
}

int main() {
    int amount_of_threads;

    std::cout << "Enter array size: ";
    std::cin >> array_size;
    arr = new int[array_size]();

    std::cout << "Enter number of threads: ";
    std::cin >> amount_of_threads;

    InitializeCriticalSection(&cs);

    HANDLE* hThreads;
    HANDLE* hThreadsStartEvents;
    HANDLE* hThreadWorkStopped;
    HANDLE* hThreadsExit;
    DWORD* dwThreads;

    initializeThreads(amount_of_threads, hThreads, hThreadsStartEvents, hThreadWorkStopped, hThreadsExit, dwThreads);
    //цикл работы
    cleanupThreads(amount_of_threads, hThreads, hThreadsStartEvents, hThreadWorkStopped, hThreadsExit);
    DeleteCriticalSection(&cs);
    delete[] arr;

    return 0;
}