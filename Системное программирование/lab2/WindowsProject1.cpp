#include <windows.h>
#include "ProgressBar.cpp"
#include <vector>

#define WM_FILLBAR 101010
#define DRAW_PROGRESS 101010
#define SET_PRIORITY_BUTTON 1
#define SUSPEND_BUTTON 2
#define RESUME_BUTTON 3
#define ID_RADIO1 4
#define ID_RADIO2 5
#define ID_RADIO3 6

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ProgressBarProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
DWORD WINAPI ThreadProc1(LPVOID lpParam);
DWORD WINAPI ThreadProc2(LPVOID lpParam);
DWORD WINAPI ThreadProc3(LPVOID lpParam);
void setPriorityButton(int index, int threadIndex);
void suspendButton(int threadIndex);
void resumeButton(int threadIndex);

HWND threadWindow;
std::vector<ProgressBar> bars;
HANDLE hThread[3];
DWORD dwThreadId[3];

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    // main window
    ZeroMemory(&wc, sizeof(WNDCLASSEX));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(255, 255, 255)));
    wc.lpszMenuName = NULL;
    wc.lpszClassName = TEXT("MyWindowClass");
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    if (!RegisterClassEx(&wc))
        return FALSE;

    wc.lpszClassName = TEXT("ProgressBar");
    wc.lpfnWndProc = ProgressBarProc;
    wc.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(200, 200, 200)));
    if (!RegisterClassEx(&wc))
        return FALSE;

    HWND hWnd = CreateWindowEx(
        0,
        TEXT("MyWindowClass"),
        TEXT("lab2 app"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
        return FALSE;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    hThread[0] = CreateThread(
        NULL,
        0,
        ThreadProc1,
        NULL,
        CREATE_SUSPENDED,
        &dwThreadId[0]);

    hThread[1] = CreateThread(
        NULL,
        0,
        ThreadProc2,
        NULL,
        CREATE_SUSPENDED,
        &dwThreadId[1]);

    hThread[2] = CreateThread(
        NULL,
        0,
        ThreadProc3,
        NULL,
        CREATE_SUSPENDED,
        &dwThreadId[2]);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

HWND hComboBox;
int selectedThread = -1;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hProgress;

    switch (message)
    {
    case WM_CREATE:
    {
        threadWindow = CreateWindowEx(
            0,
            TEXT("STATIC"),
            NULL,
            WS_CHILD | WS_VISIBLE | SS_CENTER | SS_WHITERECT,
            10, 10, 500, 300,
            hwnd,
            NULL,
            (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
            NULL
        );

        // init of 3 progress bars
        bars.push_back(ProgressBar());
        bars[bars.size() - 1].create(threadWindow, 30, 50);

        bars.push_back(ProgressBar());
        bars[bars.size() - 1].create(threadWindow, 30, 100);

        bars.push_back(ProgressBar());
        bars[bars.size() - 1].create(threadWindow, 30, 150);

        bars[0].drawProgress();

        HWND bottomMenu = CreateWindowEx(
            0,
            TEXT("STATIC"),
            NULL,
            WS_CHILD | WS_VISIBLE | SS_CENTER | SS_WHITERECT,
            10, 320, 500, 230,
            hwnd,
            NULL,
            (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
            NULL
        );
        
        hComboBox = CreateWindowEx(0, TEXT("COMBOBOX"), L"",
            WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL,
            30, 60, 320, 100, bottomMenu, NULL, NULL, NULL);

        SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)TEXT("Ниже обычного"));
        SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)TEXT("Обычный"));
        SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)TEXT("Выше обычного"));
        SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)TEXT("Высокий"));
        SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)TEXT("Реального времени"));
        SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)TEXT("Низкий"));
        SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)TEXT("Простаивающий"));

        // set priority
        CreateWindowEx(
            0,
            TEXT("BUTTON"),
            TEXT("SetPriority"),
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            40, 420, 100, 30,
            hwnd,
            (HMENU) SET_PRIORITY_BUTTON,
            (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
            NULL
        );

        // suspend
        CreateWindowEx(
            0,
            TEXT("BUTTON"),
            TEXT("Suspend"),
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            150, 420, 100, 30,
            hwnd,
            (HMENU)SUSPEND_BUTTON,
            (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
            NULL
        );

        // resume
        CreateWindowEx(
            0,
            TEXT("BUTTON"),
            TEXT("Resume"),
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            260, 420, 100, 30,
            hwnd,
            (HMENU)RESUME_BUTTON,
            (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
            NULL
        );

        CreateWindowEx(0, L"BUTTON", L"Thread 1",
            WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
            400, 400, 100, 30,
            hwnd, (HMENU)ID_RADIO1, NULL, NULL);
        CreateWindowEx(0, L"BUTTON", L"Thread 2",
            WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
            400, 440, 100, 30,
            hwnd, (HMENU)ID_RADIO2, NULL, NULL);
        CreateWindowEx(0, L"BUTTON", L"Thread 3",
            WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
            400, 480, 100, 30,
            hwnd, (HMENU)ID_RADIO3, NULL, NULL);

        SendMessage(GetDlgItem(hwnd, ID_RADIO1), BM_SETCHECK, BST_CHECKED, 0);
        selectedThread = 0;

        break;
    }

    case WM_COMMAND:
        switch(LOWORD(wParam)) { // проверка идентификатора кнопки
            case SET_PRIORITY_BUTTON:
            {
                int selectedIndex = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);
                setPriorityButton(selectedIndex, selectedThread);
                break;
            }
            case SUSPEND_BUTTON:
            {
                suspendButton(selectedThread);
                break;
            }
            case RESUME_BUTTON:
            {
                resumeButton(selectedThread);
                break;
            }
            case ID_RADIO1:
            {
                SendMessage(GetDlgItem(hwnd, ID_RADIO1), BM_SETCHECK, BST_CHECKED, 0);
                SendMessage(GetDlgItem(hwnd, ID_RADIO2), BM_SETCHECK, BST_UNCHECKED, 0);
                SendMessage(GetDlgItem(hwnd, ID_RADIO3), BM_SETCHECK, BST_UNCHECKED, 0);
                selectedThread = 0;
                break;
            }
            case ID_RADIO2:
            {
                SendMessage(GetDlgItem(hwnd, ID_RADIO1), BM_SETCHECK, BST_UNCHECKED, 0);
                SendMessage(GetDlgItem(hwnd, ID_RADIO2), BM_SETCHECK, BST_CHECKED, 0);
                SendMessage(GetDlgItem(hwnd, ID_RADIO3), BM_SETCHECK, BST_UNCHECKED, 0);
                selectedThread = 1;
                break;
            }
            case ID_RADIO3:
            {
                SendMessage(GetDlgItem(hwnd, ID_RADIO1), BM_SETCHECK, BST_UNCHECKED, 0);
                SendMessage(GetDlgItem(hwnd, ID_RADIO2), BM_SETCHECK, BST_UNCHECKED, 0);
                SendMessage(GetDlgItem(hwnd, ID_RADIO3), BM_SETCHECK, BST_CHECKED, 0);
                selectedThread = 2;
                break;
            }
        }
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        const wchar_t* text1 = TEXT("Поток 1");
        TextOut(hdc, 40, 40, text1, lstrlenW(text1));

        const wchar_t* text2 = TEXT("Поток 2");
        TextOut(hdc, 40, 90, text2, lstrlenW(text2));

        const wchar_t* text3 = TEXT("Поток 3");
        TextOut(hdc, 40, 140, text3, lstrlenW(text3));

        const wchar_t* priorityText = TEXT("Уровень приоритета");
        TextOut(hdc, 40, 350, priorityText, lstrlenW(priorityText));

        EndPaint(hwnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

// wParam is index of Bar in bars vector
LRESULT CALLBACK ProgressBarProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        // custom msg - means we need to add some progress to progressbar with index in wParam
        case WM_FILLBAR:
        {
            int barIndex = wParam;
            SendMessage(hwnd, WM_PAINT, barIndex, DRAW_PROGRESS);
            break;
        }

        case WM_PAINT:
        {
            InvalidateRect(hwnd, NULL, TRUE);
            switch (lParam)
            {
                case DRAW_PROGRESS:
                    int barIndex = wParam;
                    bars[barIndex].drawProgress();
                    break;
            } 
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

DWORD WINAPI ThreadProc1(LPVOID lpParam)
{
    while (true) {
        SendMessage(bars[0].hwnd, WM_FILLBAR, 0, 0);
        Sleep(100);
    }
    return 0;
}

DWORD WINAPI ThreadProc2(LPVOID lpParam)
{
    while (true) {
        SendMessage(bars[1].hwnd, WM_FILLBAR, 1, 0);
        Sleep(100);
    }
    return 0;
}

DWORD WINAPI ThreadProc3(LPVOID lpParam)
{
    while (true) {
        SendMessage(bars[2].hwnd, WM_FILLBAR, 2, 0);
        Sleep(100);
    }
    return 0;
}

void suspendButton(int threadIndex) {
    SuspendThread(hThread[threadIndex]);
}

void resumeButton(int threadIndex) {
    ResumeThread(hThread[threadIndex]);
}

void setPriorityButton(int index, int threadIndex) {
    if (index == -1) return;
    DWORD priorities[] = {
        THREAD_PRIORITY_BELOW_NORMAL,        THREAD_PRIORITY_NORMAL,        THREAD_PRIORITY_ABOVE_NORMAL,        THREAD_PRIORITY_HIGHEST,        THREAD_PRIORITY_TIME_CRITICAL,        THREAD_PRIORITY_LOWEST,        THREAD_PRIORITY_IDLE    };

    DWORD priority = priorities[index];

    SetThreadPriority(hThread[threadIndex], priority);
}

