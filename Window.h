#include <Windows.h>

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void Draw(HDC hdc);
void Clear(HDC hdc);
void Rotate(int);