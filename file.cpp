#include "Window.h"
#include <math.h>

const short WIDTH_WINDOW = 800;
const short HEIGHT_WINDOW = 600;

const int SIZE_SQUARE = 70;

struct Position
{
    int x;
    int y;
};

Position squarePos{WIDTH_WINDOW / 2, HEIGHT_WINDOW / 2};

POINT points[4];

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInctance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg{0};
    WNDCLASS NWC{0};
    NWC.hInstance = hInstance;
    NWC.hCursor = LoadCursor(NULL, IDC_ARROW);
    NWC.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    NWC.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
    NWC.lpfnWndProc = WindowProcedure;
    NWC.lpszClassName = TEXT("MyClassWindow");

    if (!RegisterClass(&NWC))
    {
        return -1;
    }

    HWND hwnd = CreateWindow(TEXT("MyClassWindow"), TEXT("Window"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, WIDTH_WINDOW, HEIGHT_WINDOW, NULL, NULL, NULL, NULL);

    ShowWindow(hwnd, nCmdShow);

    while (GetMessage(&msg, 0, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

void Draw(HDC hdc)
{
    HGDIOBJ hPen = SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(0, 0, 0)));
    HGDIOBJ hBrush = SelectObject(hdc, CreateSolidBrush(RGB(255, 0, 0)));
    Polygon(hdc, points, 4);
    DeleteObject(hPen);
    DeleteObject(hBrush);
}

void Clear(HDC hdc)
{
    HGDIOBJ hPen = SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(255, 255, 255)));
    HGDIOBJ hBrush = SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));
    Polygon(hdc, points, 4);
    DeleteObject(hPen);
    DeleteObject(hBrush);
}

void Rotate(HDC hdc, int angle)
{
    const double PI = 3.14159265359;

    double radians = angle * 3.14 / 180;

    double cosValue = cos(radians);
    double sinValue = sin(radians);

    Clear(hdc);

    points[0].x = -SIZE_SQUARE * cosValue + SIZE_SQUARE * sinValue + squarePos.x;
    points[0].y = SIZE_SQUARE * sinValue + SIZE_SQUARE * cosValue + squarePos.y;
    points[1].x = SIZE_SQUARE * cosValue + SIZE_SQUARE * sinValue + squarePos.x;
    points[1].y = -SIZE_SQUARE * sinValue + SIZE_SQUARE * cosValue + squarePos.y;
    points[2].x = SIZE_SQUARE * cosValue - SIZE_SQUARE * sinValue + squarePos.x;
    points[2].y = -SIZE_SQUARE * sinValue - SIZE_SQUARE * cosValue + squarePos.y;
    points[3].x = -SIZE_SQUARE * cosValue - SIZE_SQUARE * sinValue + squarePos.x;
    points[3].y = SIZE_SQUARE * sinValue - SIZE_SQUARE * cosValue + squarePos.y;

    Draw(hdc);
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch (uMsg)
    {
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        
        for (int i = 0; i < 361; i++)
        {
            Rotate(hdc, i);
            Sleep(1);
        }
        
        EndPaint(hwnd, &ps);
        break;
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    case WM_DESTROY:
        DestroyWindow(hwnd);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
        break;
    }
    return 0;
}