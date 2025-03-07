#include "framework.h"
#include "ProgressBar.cpp"


HWND threadWindow;
HWND mainWindow;
HWND contextWindow;
std::vector<ProgressBar> bars;
HANDLE hThread[3];
DWORD dwThreadId[3] = {-1, -1, -1};

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

    mainWindow = CreateWindowEx(
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

    if (!mainWindow)
        return FALSE;

    ShowWindow(mainWindow, nCmdShow);
    UpdateWindow(mainWindow);

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
            10, 10, 400, 300,
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
            10, 320, 400, 230,
            hwnd,
            NULL,
            (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
            NULL
        );
        
        hComboBox = CreateWindowEx(0, TEXT("COMBOBOX"), L"",
            WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL,
            30, 60, 220, 100, bottomMenu, NULL, NULL, NULL);

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
            30, 500, 100, 30,
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
            150, 500, 100, 30,
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
            270, 500, 100, 30,
            hwnd,
            (HMENU)RESUME_BUTTON,
            (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
            NULL
        );

        CreateWindowEx(0, L"BUTTON", L"Thread 1",
            WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
            270, 380, 100, 30,
            hwnd, (HMENU)ID_RADIO1, NULL, NULL);
        CreateWindowEx(0, L"BUTTON", L"Thread 2",
            WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
            270, 420, 100, 30,
            hwnd, (HMENU)ID_RADIO2, NULL, NULL);
        CreateWindowEx(0, L"BUTTON", L"Thread 3",
            WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
            270, 460, 100, 30,
            hwnd, (HMENU)ID_RADIO3, NULL, NULL);

        SendMessage(GetDlgItem(hwnd, ID_RADIO1), BM_SETCHECK, BST_CHECKED, 0);
        selectedThread = 0;

        HWND threadWorkWindow = CreateWindowEx(
            0,
            TEXT("STATIC"),
            NULL,
            WS_CHILD | WS_VISIBLE | SS_CENTER | SS_WHITERECT,
            420, 10, 150, 300,
            hwnd,
            NULL,
            (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
            NULL
        );

        HWND threadButtonsWindow = CreateWindowEx(
            0,
            TEXT("STATIC"),
            NULL,
            WS_CHILD | WS_VISIBLE | SS_CENTER | SS_WHITERECT,
            420, 320, 150, 230,
            hwnd,
            NULL,
            (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
            NULL
        );

        // Create(ALL)
        CreateWindowEx(
            0,
            TEXT("BUTTON"),
            TEXT("Create (All)"),
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            445, 350, 100, 30,
            hwnd,
            (HMENU)CREATE_ALL_BUTTON,
            (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
            NULL
        );

        // Start(ALL)
        CreateWindowEx(
            0,
            TEXT("BUTTON"),
            TEXT("Start (All)"),
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            445, 390, 100, 30,
            hwnd,
            (HMENU)START_ALL_BUTTON,
            (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
            NULL
        );

        // Stop(ALL)
        CreateWindowEx(
            0,
            TEXT("BUTTON"),
            TEXT("Stop (All)"),
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            445, 430, 100, 30,
            hwnd,
            (HMENU)STOP_ALL_BUTTON,
            (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
            NULL
        );

        // Terminate(ALL)
        CreateWindowEx(
            0,
            TEXT("BUTTON"),
            TEXT("Terminate (All)"),
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            445, 470, 100, 30,
            hwnd,
            (HMENU)TERMINATE_ALL_BUTTON,
            (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
            NULL
        );

        contextWindow = CreateWindowEx(
            0,
            TEXT("EDIT"),
            NULL,
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_READONLY,
            580, 10, 180, 540,
            hwnd,
            NULL,
            (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
            NULL
        );

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
                suspendThread(selectedThread);
                break;
            }
            case RESUME_BUTTON:
            {
                resumeThread(selectedThread);
                break;
            }
            case ID_RADIO1:
            {
                SendMessage(GetDlgItem(hwnd, ID_RADIO1), BM_SETCHECK, BST_CHECKED, 0);
                SendMessage(GetDlgItem(hwnd, ID_RADIO2), BM_SETCHECK, BST_UNCHECKED, 0);
                SendMessage(GetDlgItem(hwnd, ID_RADIO3), BM_SETCHECK, BST_UNCHECKED, 0);
                selectedThread = 0;
                fillThreadContext(0);
                break;
            }
            case ID_RADIO2:
            {
                SendMessage(GetDlgItem(hwnd, ID_RADIO1), BM_SETCHECK, BST_UNCHECKED, 0);
                SendMessage(GetDlgItem(hwnd, ID_RADIO2), BM_SETCHECK, BST_CHECKED, 0);
                SendMessage(GetDlgItem(hwnd, ID_RADIO3), BM_SETCHECK, BST_UNCHECKED, 0);
                selectedThread = 1;
                fillThreadContext(1);
                break;
            }
            case ID_RADIO3:
            {
                SendMessage(GetDlgItem(hwnd, ID_RADIO1), BM_SETCHECK, BST_UNCHECKED, 0);
                SendMessage(GetDlgItem(hwnd, ID_RADIO2), BM_SETCHECK, BST_UNCHECKED, 0);
                SendMessage(GetDlgItem(hwnd, ID_RADIO3), BM_SETCHECK, BST_CHECKED, 0);
                selectedThread = 2;
                fillThreadContext(2);
                break;
            }
            case CREATE_ALL_BUTTON:
            {
                CreateThreads();
                break;
            }
            case START_ALL_BUTTON:
            {
                for (int i = 0; i < 3; i++)
                {
                    resumeThread(i);
                }
                break;
            }
            case STOP_ALL_BUTTON:
            {
                for (int i = 0; i < 3; i++)
                {
                    suspendThread(i);
                }
                break;
            }
            case TERMINATE_ALL_BUTTON:
            {
                for (int i = 0; i < 3; i++)
                {
                    TerminateThread(hThread[i], 0);
                    dwThreadId[i] = -1;
                    bars[i].totalProgress = 0;
                    bars[i].currProgress = 0;
                }
                SendMessage(mainWindow, WM_PAINT, 0, 0);
                break;
            }

        }
        break;

    case WM_PAINT:
    {
        const RECT redraw = { 450, 60, 500, 180 };

        InvalidateRect(hwnd, &redraw, FALSE);

        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        std::wstring pr1 = std::to_wstring(bars[0].totalProgress);
        std::wstring pr2 = std::to_wstring(bars[1].totalProgress);
        std::wstring pr3 = std::to_wstring(bars[2].totalProgress);

        const wchar_t* text1 = TEXT("Поток 1");
        TextOut(hdc, 40, 40, text1, lstrlenW(text1));
        TextOut(hdc, 450, 40, text1, lstrlenW(text1));
        TextOut(hdc, 450, 60, pr1.c_str(), static_cast<int>(pr1.size()));

        const wchar_t* text2 = TEXT("Поток 2");
        TextOut(hdc, 40, 90, text2, lstrlenW(text2));
        TextOut(hdc, 450, 90, text2, lstrlenW(text2));
        TextOut(hdc, 450, 110, pr2.c_str(), static_cast<int>(pr2.size()));

        const wchar_t* text3 = TEXT("Поток 3");
        TextOut(hdc, 40, 140, text3, lstrlenW(text3));
        TextOut(hdc, 450, 140, text3, lstrlenW(text3));
        TextOut(hdc, 450, 160, pr3.c_str(), static_cast<int>(pr3.size()));

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
            switch (lParam)
            {
                case DRAW_PROGRESS:
                    InvalidateRect(hwnd, NULL, TRUE);
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


void CreateThreads() {
    if (dwThreadId[0] != -1 || dwThreadId[1] != -1 || dwThreadId[2] != -1) {
        for (int i = 0; i < 3; i++)
        {
            TerminateThread(hThread[i], 0);
            dwThreadId[i] = -1;
            bars[i].totalProgress = 0;
            bars[i].currProgress = 0;
        }
        SendMessage(mainWindow, WM_PAINT, 0, 0);
    }

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
}

DWORD WINAPI ThreadProc1(LPVOID lpParam)
{
    while (true) {
        SendMessage(bars[0].hwnd, WM_FILLBAR, 0, 0);
        SendMessage(mainWindow, WM_PAINT, 0, 0);
        Sleep(100);
    }
    return 0;
}

DWORD WINAPI ThreadProc2(LPVOID lpParam)
{
    while (true) {
        SendMessage(bars[1].hwnd, WM_FILLBAR, 1, 0);
        SendMessage(mainWindow, WM_PAINT, 0, 0);
        Sleep(100);
    }
    return 0;
}

DWORD WINAPI ThreadProc3(LPVOID lpParam)
{
    while (true) {
        SendMessage(bars[2].hwnd, WM_FILLBAR, 2, 0);
        SendMessage(mainWindow, WM_PAINT, 0, 0);
        Sleep(100);
    }
    return 0;
}

void suspendThread(int threadIndex) {
    SuspendThread(hThread[threadIndex]);
}

void resumeThread(int threadIndex) {
    ResumeThread(hThread[threadIndex]);
}

void setPriorityButton(int index, int threadIndex) {
    if (index == -1) return;
    DWORD priorities[] = {
        THREAD_PRIORITY_BELOW_NORMAL,
        THREAD_PRIORITY_NORMAL,
        THREAD_PRIORITY_ABOVE_NORMAL,
        THREAD_PRIORITY_HIGHEST,
        THREAD_PRIORITY_TIME_CRITICAL,
        THREAD_PRIORITY_LOWEST,
        THREAD_PRIORITY_IDLE
    };

    DWORD priority = priorities[index];

    SetThreadPriority(hThread[threadIndex], priority);
}

void fillThreadContext(int threadIndex) {
    CONTEXT ct;
    std::wstring out = TEXT("CONTEXT OF THREAD ");
    if (GetThreadContext(hThread[threadIndex], &ct) == 0) {
        DWORD errorCode = GetLastError();

        LPWSTR messageBuffer = nullptr;
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPWSTR)&messageBuffer, 0, nullptr);

        if (messageBuffer != nullptr) {
            out = TEXT("Не удалось получить контекст потока.\r\nКод ошибки: ");
            out += std::to_wstring(errorCode);
            out += TEXT(".\r\nОписание ошибки: ");
            out += messageBuffer;

            LocalFree(messageBuffer);
        }
        else {
            out = TEXT("Не удалось получить контекст потока. Код ошибки: ") + std::to_wstring(errorCode);
        }

        SendMessage(contextWindow, WM_SETTEXT, 0, (LPARAM)out.c_str());
        SendMessage(contextWindow, WM_PAINT, 0, 0);
        return;
    }

    out = TEXT("CONTEXT OF THREAD ");
    out += std::to_wstring(threadIndex + 1);

    out += TEXT("\r\nContextFlags: ");
    out += std::to_wstring(ct.ContextFlags);

    out += TEXT("\r\nEax: ");
    out += std::to_wstring(ct.Eax);

    out += TEXT("\r\nEbx: ");
    out += std::to_wstring(ct.Ebx);

    out += TEXT("\r\nEbp: ");
    out += std::to_wstring(ct.Ebp);

    out += TEXT("\r\nEcx: ");
    out += std::to_wstring(ct.Ecx);

    out += TEXT("\r\nEdx: ");
    out += std::to_wstring(ct.Edx);

    out += TEXT("\r\nEdi: ");
    out += std::to_wstring(ct.Edi);

    out += TEXT("\r\nEsp: ");
    out += std::to_wstring(ct.Esp);

    out += TEXT("\r\nEip: ");
    out += std::to_wstring(ct.Eip);

    out += TEXT("\r\nEsi: ");
    out += std::to_wstring(ct.Esi);

    out += TEXT("\r\nEsp: ");
    out += std::to_wstring(ct.Esp);

    out += TEXT("\r\nDr0: ");
    out += std::to_wstring(ct.Dr0);

    out += TEXT("\r\nDr1: ");
    out += std::to_wstring(ct.Dr1);

    out += TEXT("\r\nDr2: ");
    out += std::to_wstring(ct.Dr2);

    out += TEXT("\r\nDr3: ");
    out += std::to_wstring(ct.Dr3);

    out += TEXT("\r\nDr6: ");
    out += std::to_wstring(ct.Dr6);

    out += TEXT("\r\nDr7: ");
    out += std::to_wstring(ct.Dr7);

    out += TEXT("\r\nSegCs: ");
    out += std::to_wstring(ct.SegCs);

    out += TEXT("\r\nSegDs: ");
    out += std::to_wstring(ct.SegDs);

    out += TEXT("\r\nSegEs: ");
    out += std::to_wstring(ct.SegEs);

    out += TEXT("\r\nSegFs: ");
    out += std::to_wstring(ct.SegFs);

    out += TEXT("\r\nSegGs: ");
    out += std::to_wstring(ct.SegGs);

    out += TEXT("\r\nSegSs: ");
    out += std::to_wstring(ct.SegSs);


    SendMessage(contextWindow, WM_SETTEXT, 0, (LPARAM)out.c_str());
    SendMessage(contextWindow, WM_PAINT, 0, 0);
}

