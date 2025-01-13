﻿#ifndef LAB3_H
#define LAB3_H

#include <Windows.h>
#include <iostream>

extern int array_size;
extern int* arr;
extern CRITICAL_SECTION cs;

DWORD WINAPI marker(LPVOID thread_index);

void initializeThreads(int amount_of_threads, HANDLE*& hThreads, HANDLE*& hThreadsStartEvents, HANDLE*& hThreadWorkStopped, HANDLE*& hThreadsExit, DWORD*& dwThreads);
void cleanupThreads(int amount_of_threads, HANDLE*& hThreads, HANDLE*& hThreadsStartEvents, HANDLE*& hThreadWorkStopped, HANDLE*& hThreadsExit);

#endif