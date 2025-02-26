#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(WNDCLASSEX));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(66, 245, 245)));
    wc.lpszMenuName = NULL;
    wc.lpszClassName = TEXT("MyWindowClass");
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
        return FALSE;

    HWND hWnd = CreateWindowEx(
        0,
        TEXT("MyWindowClass"),
        TEXT("lab1 app"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        600, 400,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
        return FALSE;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

void ClientDraw(HWND hwnd, WPARAM wParam, LPARAM lParam) {
    TCHAR str[] = TEXT("Ура! Мы сделали это!!!");
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    TextOut(hdc, 50, 20, str, wcslen(str));
    
    // base primitives
    Rectangle(hdc, 30, 50, 70, 80);
    Ellipse(hdc, 30, 90, 70, 120);

    // line
    MoveToEx(hdc, 30, 130, NULL);
    LineTo(hdc, 70, 130);

    //triangle
    MoveToEx(hdc, 30, 140, NULL);
    POINT Points[] = { 70,140, 50,160, 30,140 };
    PolylineTo(hdc, Points, 3);

    // Вариант 4
    LOGBRUSH lb;
    lb.lbStyle = BS_SOLID;
    lb.lbColor = RGB(0, 0, 255);
    lb.lbHatch = 0;

    // Синий пунктир ширины 3
    HGDIOBJ ellipsePen = ExtCreatePen(PS_GEOMETRIC | PS_DASH, 3, &lb, 0, NULL);
    // Зеленый сплошной ширины 6
    lb.lbColor = RGB(0, 255, 0);
    HGDIOBJ crossPen = ExtCreatePen(PS_GEOMETRIC | PS_SOLID, 6, &lb, 0, NULL);

    HGDIOBJ oldPen = SelectObject(hdc, ellipsePen);

    Ellipse(hdc, 300, 30, 450, 120);

    SelectObject(hdc, crossPen);

    MoveToEx(hdc, 300, 30, NULL);
    LineTo(hdc, 450, 120);

    MoveToEx(hdc, 300, 120, NULL);
    LineTo(hdc, 450, 30);

    SelectObject(hdc, oldPen);

    DeleteObject(crossPen);
    DeleteObject(ellipsePen);

    EndPaint(hwnd, &ps);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_PAINT:
        ClientDraw(hwnd, wParam, lParam);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}