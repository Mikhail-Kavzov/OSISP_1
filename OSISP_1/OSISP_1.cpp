#pragma once
#include <Windows.h>
#include "Ellipse.h"
#include "Rectange.h"
#include "Image.h"

using namespace MColor;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

auto const CLASS_NAME = L"Sprite"; //window class name
const int spriteDelta = 5; // delta for sprite movement
const int spriteArrLen = 3; //array length of entities
const int jumpLen = 20; //rebound from a border

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(wc.hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = HBRUSH(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"Sprite";
	wc.hIconSm = LoadIcon(wc.hInstance, IDI_APPLICATION);

	RegisterClassEx(&wc);
	HWND hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		CLASS_NAME,
		L"OSiSP",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 400,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){	

	RECT rc;
	PAINTSTRUCT ps;
	HDC hdc;
	static Drawing::Entity** sprite;
	static int sPos = 0;
	GetClientRect(hWnd, &rc);
	switch (uMsg) {
		case WM_CREATE: {
			sprite= new Drawing::Entity*[spriteArrLen] {
				new Drawing::Ellipse(150, 100, 100, 50),
				new Drawing::Rectangle(50, 50, 200, 100),
				new Drawing::Image(50, 50, L"../i4.bmp")
			};
			break;
		}
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_PAINT: {
			hdc = BeginPaint(hWnd, &ps);
			auto hdcMem = CreateCompatibleDC(hdc);
			auto hbmMem = CreateCompatibleBitmap(hdc,
				rc.right - rc.left,
				rc.bottom - rc.top);
			auto hbmOld = SelectObject(hdcMem, hbmMem);
			auto hbrBkGnd = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
			FillRect(hdcMem, &rc, hbrBkGnd);
			DeleteObject(hbrBkGnd);
			sprite[sPos]->Draw(hdcMem);
			BitBlt(hdc,
				rc.left, rc.top,
				rc.right - rc.left, rc.bottom - rc.top,
				hdcMem,
				0, 0,
				SRCCOPY);
			SelectObject(hdcMem, hbmOld);
			DeleteObject(hbmMem);
			DeleteDC(hdcMem);
			
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_MOUSEWHEEL: {
			int offset = GET_WHEEL_DELTA_WPARAM(wParam);
			if (LOWORD(wParam) == MK_SHIFT) {
				if (offset > 0) { //left
					sprite[sPos]->Move(-spriteDelta, 0);
					if (sprite[sPos]->IsBorder(rc.left,rc.top,rc.right,rc.bottom))
						sprite[sPos]->Move(jumpLen, 0);
				}
				else {//right
					sprite[sPos]->Move(spriteDelta, 0);
					if (sprite[sPos]->IsBorder(rc.left, rc.top, rc.right, rc.bottom))
						sprite[sPos]->Move(-jumpLen, 0);
				}
			}
			else {
				if (offset > 0) { //up
					sprite[sPos]->Move(0, -spriteDelta);
					if (sprite[sPos]->IsBorder(rc.left, rc.top, rc.right, rc.bottom))
						sprite[sPos]->Move(0,jumpLen);
				}
				else {//down
					sprite[sPos]->Move(0, spriteDelta);
					if (sprite[sPos]->IsBorder(rc.left, rc.top, rc.right, rc.bottom))
						sprite[sPos]->Move(0, -jumpLen);
				}
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case WM_KEYDOWN: {
			switch (wParam) {
				case VK_LEFT:{	//left key
					sprite[sPos]->Move(-spriteDelta, 0);
					if (sprite[sPos]->IsBorder(rc.left, rc.top, rc.right, rc.bottom))
					sprite[sPos]->Move(jumpLen, 0);	
					break;
				}					
				case VK_RIGHT:{ //right key
					sprite[sPos]->Move(spriteDelta, 0);
					if (sprite[sPos]->IsBorder(rc.left, rc.top, rc.right, rc.bottom))
						sprite[sPos]->Move(-jumpLen, 0);
					break;
				}					
				case VK_UP:{ //up key	
					sprite[sPos]->Move(0, -spriteDelta);
					if (sprite[sPos]->IsBorder(rc.left, rc.top, rc.right, rc.bottom))
						sprite[sPos]->Move(0, jumpLen);
					break;
				}
				case VK_DOWN:{ //down key
					sprite[sPos]->Move(0, spriteDelta);
					if (sprite[sPos]->IsBorder(rc.left, rc.top, rc.right, rc.bottom))
						sprite[sPos]->Move(0, -jumpLen);
					break;
				}
				case VK_SPACE:{ //backspace - change object
					++sPos;
					if (sPos == spriteArrLen)
						sPos = 0;					
					break;
				}
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case WM_GETMINMAXINFO: { //min size
			MINMAXINFO* minMaxSize = (MINMAXINFO*)lParam;
			minMaxSize->ptMinTrackSize = POINT(500, 500);
			break;
		}
		case WM_ERASEBKGND: //double buffered
			break;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}
