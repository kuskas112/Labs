#include <windows.h>
#include <tchar.h>
#include <fstream>
#include <string>
#include <system_error>

// Глобальные переменные
HWND hEdit1, hEdit2;

// Прототип функции обработки сообщений
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Регистрация класса окна
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = _T("MyWindowClass");
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, _T("Ошибка регистрации класса окна!"), _T("Ошибка"), MB_ICONERROR);
        return 0;
    }

    // Создание окна
    HWND hWnd = CreateWindow(
        _T("MyWindowClass"),
        _T("practice 1"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
        NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        MessageBox(NULL, _T("Ошибка создания окна!"), _T("Ошибка"), MB_ICONERROR);
        return 0;
    }

    // Показать окно
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Цикл сообщений
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

void OnButtonClick(HWND hWnd)
{
    // Получаем пути к файлам из полей ввода
    wchar_t sourceFilePath[MAX_PATH] = { 0 };
    wchar_t destFilePath[MAX_PATH] = { 0 };

    GetWindowTextW(hEdit1, sourceFilePath, MAX_PATH);
    GetWindowTextW(hEdit2, destFilePath, MAX_PATH);

    // Проверяем, что пути не пустые
    if (sourceFilePath[0] == L'\0' || destFilePath[0] == L'\0')
    {
        MessageBoxW(hWnd, L"Оба поля должны содержать пути к файлам!", L"Ошибка", MB_ICONERROR);
        return;
    }

    // Открываем исходный файл для чтения
    HANDLE hSourceFile = CreateFileW(
        sourceFilePath,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (hSourceFile == INVALID_HANDLE_VALUE)
    {
        MessageBoxW(hWnd, L"Не удалось открыть исходный файл!", L"Ошибка", MB_ICONERROR);
        return;
    }

    // Создаем (или перезаписываем) целевой файл
    HANDLE hDestFile = CreateFileW(
        destFilePath,
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (hDestFile == INVALID_HANDLE_VALUE)
    {
        CloseHandle(hSourceFile);
        MessageBoxW(hWnd, L"Не удалось создать целевой файл!", L"Ошибка", MB_ICONERROR);
        return;
    }

    // Копируем содержимое
    const DWORD bufferSize = 256;
    BYTE buffer[bufferSize];
    DWORD bytesRead = 0;
    DWORD bytesWritten = 0;
    BOOL success = TRUE;

    while (success && ReadFile(hSourceFile, buffer, bufferSize, &bytesRead, NULL) && bytesRead > 0)
    {
        success = WriteFile(hDestFile, buffer, bytesRead, &bytesWritten, NULL);
        if (!success || bytesWritten != bytesRead)
        {
            MessageBoxW(hWnd, L"Ошибка записи в целевой файл!", L"Ошибка", MB_ICONERROR);
            break;
        }
    }

    // Закрываем дескрипторы файлов
    CloseHandle(hSourceFile);
    CloseHandle(hDestFile);

    if (success)
    {
        MessageBoxW(hWnd, L"Файл успешно скопирован!", L"Успех", MB_OK);
    }
}

void OnButtonClickCopyFileFunc(HWND hWnd)
{
    wchar_t sourceFilePath[MAX_PATH] = { 0 };
    wchar_t destFilePath[MAX_PATH] = { 0 };

    GetWindowTextW(hEdit1, sourceFilePath, MAX_PATH);
    GetWindowTextW(hEdit2, destFilePath, MAX_PATH);

    if (sourceFilePath[0] == L'\0' || destFilePath[0] == L'\0')
    {
        MessageBoxW(hWnd, L"Оба поля должны содержать пути к файлам!", L"Ошибка", MB_ICONERROR);
        return;
    }

    if (CopyFileW(sourceFilePath, destFilePath, FALSE)) // FALSE = разрешить перезапись
    {
        MessageBoxW(hWnd, L"Файл успешно скопирован!", L"Успех", MB_OK);
    }
    else
    {
        wchar_t errorMsg[256];
        swprintf_s(errorMsg, L"Ошибка копирования (код: %d)", GetLastError());
        MessageBoxW(hWnd, errorMsg, L"Ошибка", MB_ICONERROR);
    }
}

void OnButtonClickOnlyC(HWND hWnd)
{
    wchar_t sourceFilePath[MAX_PATH] = { 0 };
    wchar_t destFilePath[MAX_PATH] = { 0 };

    GetWindowTextW(hEdit1, sourceFilePath, MAX_PATH);
    GetWindowTextW(hEdit2, destFilePath, MAX_PATH);

    if (sourceFilePath[0] == L'\0' || destFilePath[0] == L'\0')
    {
        MessageBoxW(hWnd, L"Оба поля должны содержать пути к файлам!", L"Ошибка", MB_ICONERROR);
        return;
    }

    try
    {
        std::ifstream sourceFile(sourceFilePath, std::ios::binary);
        if (!sourceFile)
        {
            throw std::runtime_error("Не удалось открыть исходный файл!");
        }

        std::ofstream destFile(destFilePath, std::ios::binary | std::ios::trunc);
        if (!destFile)
        {
            throw std::runtime_error("Не удалось создать целевой файл!");
        }

        destFile << sourceFile.rdbuf();

        if (!destFile)
        {
            throw std::runtime_error("Ошибка записи в целевой файл!");
        }

        MessageBoxW(hWnd, L"Файл успешно скопирован!", L"Успех", MB_OK);
    }
    catch (const std::exception& e)
    {
        // Конвертируем сообщение об ошибке в Unicode для MessageBoxW
        std::string utf8Error = e.what();
        int wideSize = MultiByteToWideChar(CP_UTF8, 0, utf8Error.c_str(), -1, nullptr, 0);
        std::wstring wideError(wideSize, L'\0');
        MultiByteToWideChar(CP_UTF8, 0, utf8Error.c_str(), -1, &wideError[0], wideSize);

        MessageBoxW(hWnd, wideError.c_str(), L"Ошибка", MB_ICONERROR);
    }
}

// Оконная процедура
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        // Создаем первое поле ввода
        hEdit1 = CreateWindow(
            _T("EDIT"),
            _T("D:\\file1.txt"),
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            20, 20, 350, 25,
            hWnd,
            NULL,
            ((LPCREATESTRUCT)lParam)->hInstance,
            NULL);

        // Создаем второе поле ввода
        hEdit2 = CreateWindow(
            _T("EDIT"),
            _T("D:\\file2.txt"),
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            20, 60, 350, 25,
            hWnd,
            NULL,
            ((LPCREATESTRUCT)lParam)->hInstance,
            NULL);

        CreateWindow(
            _T("BUTTON"),
            _T("Ручное win32 копирование"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            20, 100, 300, 30,
            hWnd,
            (HMENU)1,
            ((LPCREATESTRUCT)lParam)->hInstance,
            NULL);

        CreateWindow(
            _T("BUTTON"),
            _T("Полуфабрикатное win32 копирование"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            20, 150, 300, 30,
            hWnd,
            (HMENU)2,
            ((LPCREATESTRUCT)lParam)->hInstance,
            NULL);

        CreateWindow(
            _T("BUTTON"),
            _T("Стандартное копирование"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            20, 200, 300, 30,
            hWnd,
            (HMENU)3,
            ((LPCREATESTRUCT)lParam)->hInstance,
            NULL);
    }
    break;

    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case 1:  // ручное win32
            OnButtonClick(hWnd);
            break;
        case 2:  // полуфабрикатное win32
            OnButtonClickCopyFileFunc(hWnd);
            break;
        case 3:  // только с++
            OnButtonClickOnlyC(hWnd);
            break;
        }
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}