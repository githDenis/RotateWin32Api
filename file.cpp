#include "Window.h"

const short WIDTH_WINDOW = 800;
const short HEIGHT_WINDOW = 600;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInctance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg{ 0 };
    WNDCLASS NWC{ 0 };
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

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
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