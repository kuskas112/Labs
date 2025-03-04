#include <windows.h>

class ProgressBar {
private:
	int WIDTH = 300;
	int HEIGHT = 10;
	int x = 0, y = 0;
    int speed = 5;
public:
	HWND hwnd;
    int totalProgress = 0;
    int currProgress = 0;


    void create(HWND parent, int x, int y) {
        hwnd = CreateWindowEx(
            0,
            TEXT("ProgressBar"),
            NULL,
            WS_CHILD | WS_VISIBLE,
            x, y, WIDTH, HEIGHT,
            parent,
            NULL,
            (HINSTANCE)GetWindowLong(parent, GWL_HINSTANCE),
            NULL
        );

        this->x = x;
        this->y = y;
    }

    void drawProgress() {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
        SelectObject(hdc, hBrush);
        currProgress = (currProgress + speed) % WIDTH;
        totalProgress += speed;
        Rectangle(hdc, 0, 0, currProgress, HEIGHT);
        DeleteObject(hBrush);
        EndPaint(hwnd, &ps);
    }
};