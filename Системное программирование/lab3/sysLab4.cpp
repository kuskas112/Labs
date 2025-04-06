// sysLab4.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "sysLab4.h"
#include "Resource.h"
#include <fstream>

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
HWND mainWindow;
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void DrawBMP(HDC hdc, HBITMAP hBitmap, int x, int y);

HBITMAP LoadBitmapFromFile(HDC hdc, const wchar_t* filename);

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

    return RegisterClassExW(&wcex);
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
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!mainWindow)
   {
      return FALSE;
   }

   ShowWindow(mainWindow, nCmdShow);
   UpdateWindow(mainWindow);

   return TRUE;
}

HBITMAP LoadSpecialBitmap(int resourceId, UINT bitsPerPixel) {
    return (HBITMAP)LoadImage(
        GetModuleHandle(NULL),
        MAKEINTRESOURCE(resourceId),
        IMAGE_BITMAP,
        0, 0,
        LR_CREATEDIBSECTION | (bitsPerPixel == 16 ? LR_VGACOLOR : 0)
    );
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HBITMAP hBitmap = nullptr;
    switch (message)
    {
    case WM_CREATE:
        {
            // Пример использования:
            
        }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            hBitmap = LoadBitmapFromFile(hdc, L"D:\\32.bmp"); // Рисуем BMP в (10, 10)
            DrawBMP(hdc, hBitmap, 10, 10);

            EndPaint(hWnd, &ps);
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

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
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
            hdc, 10, 10, 500, 500,
            hMemDC, 0, 0, bmp.bmWidth, bmp.bmHeight,
            SRCCOPY
        );

        //StretchDIBits(
        //    hdc,
        //    x, y,
        //    500, 500, // Размер вывода (можно заменить на bmp.bmWidth, bmp.bmHeight для 1:1)
        //    0, 0,
        //    ds.dsBmih.biWidth, abs(ds.dsBmih.biHeight), // abs для отрицательной высоты
        //    ds.dsBm.bmBits,
        //    (BITMAPINFO*)&ds.dsBmih,
        //    DIB_RGB_COLORS,
        //    SRCCOPY
        //);
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

