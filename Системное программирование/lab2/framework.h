#pragma once

#include <windows.h>
#include <vector>
#include <string>

#define WM_FILLBAR 101010
#define DRAW_PROGRESS 101010
#define SET_PRIORITY_BUTTON 1
#define SUSPEND_BUTTON 2
#define RESUME_BUTTON 3
#define ID_RADIO1 4
#define ID_RADIO2 5
#define ID_RADIO3 6
#define CREATE_ALL_BUTTON 7
#define START_ALL_BUTTON 8
#define STOP_ALL_BUTTON 9
#define TERMINATE_ALL_BUTTON 10

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ProgressBarProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
DWORD WINAPI ThreadProc1(LPVOID lpParam);
DWORD WINAPI ThreadProc2(LPVOID lpParam);
DWORD WINAPI ThreadProc3(LPVOID lpParam);
void setPriorityButton(int index, int threadIndex);
void fillThreadContext(int threadIndex);
void suspendThread(int threadIndex);
void resumeThread(int threadIndex);
void CreateThreads();