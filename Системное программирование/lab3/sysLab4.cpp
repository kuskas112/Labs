// sysLab4.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "sysLab4.h"
#include "Resource.h"
#include <fstream>

#define MAX_LOADSTRING 100
#define DRAW_BMP 101
#define WM_SET_BITMAP 102
#define WM_UPDATE_PARAM 103
#define ANIMATION_TIMER_ID 228

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
HWND mainWindow;
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
int wndHeight = 600, wndWidth = 900;
HANDLE hThread[3];
DWORD dwThreadId[3] = { -1, -1, -1 };
const wchar_t* file1 = L"D:\\12.bmp";
const wchar_t* file2 = L"D:\\16.bmp";
const wchar_t* file3 = L"D:\\32.bmp";

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK bmpWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void DrawBMP(HDC hdc, HBITMAP hBitmap, int x, int y);

HBITMAP LoadBitmapFromFile(HDC hdc, const wchar_t* filename);

DWORD __stdcall ThreadProc(LPVOID lpParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SYSLAB4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SYSLAB4));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SYSLAB4));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SYSLAB4);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    bool res = RegisterClassExW(&wcex);

    wcex.lpszClassName = L"bmpWindow";
    wcex.lpfnWndProc = bmpWndProc;

    res = res && RegisterClassExW(&wcex);
    return res;
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   mainWindow = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, wndWidth, wndHeight, nullptr, nullptr, hInstance, nullptr);

   if (!mainWindow)
   {
      return FALSE;
   }

   ShowWindow(mainWindow, nCmdShow);
   UpdateWindow(mainWindow);

   return TRUE;
}

struct LPPARAM {
    HWND tab = nullptr;
    const wchar_t* filepath;
    int tabIndex = 0;
};

struct bmpData {
    HBITMAP hBitmap = nullptr;
    int y = 300;
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HBITMAP hBitmap = nullptr;
    switch (message)
    {
    case WM_CREATE:
        {
            HWND tab1 = CreateWindow(
                L"bmpWindow",
                NULL,
                WS_CHILD | WS_VISIBLE | SS_BLACKFRAME,
                10, 10,  // Позиция
                (wndWidth-10) / 3, wndHeight - 80, // Размер
                hWnd,
                (HMENU)1,
                ((LPCREATESTRUCT)lParam)->hInstance,
                NULL
            );
            LPPARAM* params1 = new LPPARAM;
            params1->tab = tab1;
            params1->filepath = L"D:\\12.bmp";
            params1->tabIndex = 0;
            hThread[0] = CreateThread(
                NULL,
                0,
                ThreadProc,
                (LPVOID)params1,
                0,
                &dwThreadId[0]);

            HWND tab2 = CreateWindow(
                L"bmpWindow",
                NULL,
                WS_CHILD | WS_VISIBLE | SS_BLACKFRAME,
                10 + (wndWidth / 3), 10,  // Позиция
                (wndWidth - 10) / 3, wndHeight - 80, // Размер
                hWnd,
                (HMENU)1,
                ((LPCREATESTRUCT)lParam)->hInstance,
                NULL
            );

            LPPARAM* params2 = new LPPARAM;
            params2->tab = tab2;
            params2->filepath = L"D:\\16.bmp";
            params2->tabIndex = 1;
            hThread[1] = CreateThread(
                NULL,
                0,
                ThreadProc,
                (LPVOID)params2,
                0,
                &dwThreadId[1]);

            HWND tab3 = CreateWindow(
                L"bmpWindow",
                NULL,
                WS_CHILD | WS_VISIBLE | SS_BLACKFRAME,
                10 + (wndWidth / 3 * 2), 10,  // Позиция
                (wndWidth - 10) / 3 - 30, wndHeight - 80, // Размер
                hWnd,
                (HMENU)1,
                ((LPCREATESTRUCT)lParam)->hInstance,
                NULL
            );

            LPPARAM* params3 = new LPPARAM;
            params3->tab = tab3;
            params3->filepath = L"D:\\32.bmp";
            params3->tabIndex = 2;
            hThread[2] = CreateThread(
                NULL,
                0,
                ThreadProc,
                (LPVOID)params3,
                0,
                &dwThreadId[2]);

            
            break;
        }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK bmpWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        bmpData* pData = new bmpData;
        pData->hBitmap = nullptr;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pData);

        SetTimer(hWnd,             // Дескриптор окна
            ANIMATION_TIMER_ID, // Идентификатор таймера (уникальное число)
            30,                // Интервал в миллисекундах
            NULL);             // Функция обратного вызова (NULL для WM_TIMER)
        break;
    }

    case WM_TIMER:
        //if (wParam == ANIMATION_TIMER_ID) {  // Проверяем наш таймер
        //    bmpData* pData = (bmpData*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        //    if (pData) {
        //        pData->y -= 1;  // Например, двигаем изображение вниз
        //        if (pData->y < 0) pData->y = wndHeight - 100;  // Циклическая анимация
        //        // Запрашиваем перерисовку
        //        InvalidateRect(hWnd, NULL, TRUE);
        //    }
        //}
        break;

    case WM_SET_BITMAP: 
    {
        // wParam - новый HBITMAP
        bmpData* pData = (bmpData*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        if (pData->hBitmap) DeleteObject(pData->hBitmap); // Удаляем старый
        pData->hBitmap = (HBITMAP)wParam; // Сохраняем новый
        InvalidateRect(hWnd, NULL, TRUE); // Запрашиваем перерисовку
        break;
    }

    case WM_UPDATE_PARAM: {
        bmpData* pData = (bmpData*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        if (pData) {
            pData->y = (int)wParam;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        RECT rect;
        GetClientRect(hWnd, &rect);
        Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
        
        bmpData* pData = (bmpData*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        if (pData && pData->hBitmap) {
            DrawBMP(hdc, pData->hBitmap, 100, pData->y);
        }

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY:
    {
        bmpData* pData = (bmpData*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        if (pData) {
            if (pData->hBitmap) DeleteObject(pData->hBitmap);
            delete pData;
        }
        PostQuitMessage(0);
        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void DrawBMP(HDC hdc, HBITMAP hBitmap, int x, int y) {
    // Создаём совместимый контекст устройства
    HDC hMemDC = CreateCompatibleDC(hdc);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

    // Получаем информацию о битмапе
    BITMAP bmp;
    GetObject(hBitmap, sizeof(BITMAP), &bmp);

    // Получаем полную информацию о DIB
    DIBSECTION ds;
    if (GetObject(hBitmap, sizeof(DIBSECTION), &ds) == 0) {
        // Если не DIB-секция, используем обычный BitBlt
        BITMAP bm;
        GetObject(hBitmap, sizeof(BITMAP), &bm);

        BitBlt(hdc, x, y, bm.bmWidth, bm.bmHeight, hMemDC, 0, 0, SRCCOPY);
    }
    else {
        // Для DIB-секции используем StretchDIBits для точного вывода
        StretchBlt(
            hdc, x, y, 100, 100,
            hMemDC, 0, 0, bmp.bmWidth, bmp.bmHeight,
            SRCCOPY
        );
    }

    // Восстанавливаем и освобождаем ресурсы
    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);
}


HBITMAP LoadBitmapFromFile(HDC hdc, const wchar_t* filename) {
    // Открытие файла
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        MessageBoxA(NULL, "Не удалось открыть файл", "Ошибка", MB_ICONERROR);
        return nullptr;
    }

    // Считывание заголовков
    BITMAPFILEHEADER bmfh;
    file.read(reinterpret_cast<char*>(&bmfh), sizeof(bmfh));

    BITMAPINFOHEADER bmih;
    file.read(reinterpret_cast<char*>(&bmih), sizeof(bmih));

    // Проверка типа файла
    if (bmfh.bfType != 0x4D42) { // 'BM'
        MessageBoxA(NULL, "Неверный тип файла", "Ошибка", MB_ICONERROR);
        return nullptr;
    }

    int stride = ((bmih.biWidth * bmih.biBitCount + 31) / 32) * 4;
    int totalBytes = stride * abs(bmih.biHeight);

    // Подготовка структуры BITMAPINFO с палитрой
    int extraSize = bmih.biBitCount <= 8 ? sizeof(RGBQUAD) * pow(2, bmih.biBitCount) : 0;
    bmih.biCompression = 0;
    BITMAPINFO* bmi = (BITMAPINFO*)new char[sizeof(BITMAPINFO) + extraSize];
    memcpy(&bmi->bmiHeader, &bmih, sizeof(BITMAPINFOHEADER));

    if (bmih.biBitCount <= 8) {
        file.read(reinterpret_cast<char*>(bmi->bmiColors), sizeof(RGBQUAD) * pow(2, bmih.biBitCount));
    }

    void* bits = nullptr;
    HBITMAP hBitmap = CreateDIBSection(hdc, bmi, DIB_RGB_COLORS, &bits, NULL, 0);
    if (!hBitmap) {
        MessageBoxA(NULL, "Ошибка создания DIB-секции", "Ошибка", MB_ICONERROR);
        delete[] bmi;
        return nullptr;
    }

    // Чтение пиксельных данных
    file.seekg(bmfh.bfOffBits, std::ios_base::beg);
    file.read(static_cast<char*>(bits), totalBytes);

    return hBitmap;
}

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
    LPPARAM* pParams = (LPPARAM*)lpParam;
    HWND tab = pParams->tab;
    const wchar_t* filepath = pParams->filepath;
    HDC hdc = GetDC(tab);
    HBITMAP hBitmap = LoadBitmapFromFile(hdc, filepath);
    // Отправляем в UI-поток
    PostMessage(tab, WM_SET_BITMAP, (WPARAM)hBitmap, 0);
    Sleep(2000 + 1000 * pParams->tabIndex);
    int y = 300;
    int mul = 1;
    while (true) {
        Sleep(40);
        PostMessage(tab, WM_UPDATE_PARAM, (WPARAM)y, 0);
        y -= 5 * mul;
        if (y <= 20 || y > wndHeight - 200) mul *= -1;
    }
    return 0;
}

void CreateThreads() {
    if (dwThreadId[0] != -1 || dwThreadId[1] != -1 || dwThreadId[2] != -1) {
        for (int i = 0; i < 3; i++)
        {
            TerminateThread(hThread[i], 0);
            dwThreadId[i] = -1;
        }
        SendMessage(mainWindow, WM_PAINT, 0, 0);
    }

    hThread[0] = CreateThread(
        NULL,
        0,
        ThreadProc,
        (LPVOID)file1,
        CREATE_SUSPENDED,
        &dwThreadId[0]);

    hThread[1] = CreateThread(
        NULL,
        0,
        ThreadProc,
        (LPVOID)file2,
        CREATE_SUSPENDED,
        &dwThreadId[1]);

    hThread[2] = CreateThread(
        NULL,
        0,
        ThreadProc,
        (LPVOID)file3,
        CREATE_SUSPENDED,
        &dwThreadId[2]);
}

