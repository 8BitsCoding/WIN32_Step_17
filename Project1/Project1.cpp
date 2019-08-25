// Project1.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Project1.h"

wchar_t g_time_str[64];
int g_time_len;
HFONT gh_font;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_PAINT) {
		PAINTSTRUCT ps;
		HDC h_dc = BeginPaint(hWnd, &ps);

		RECT r;
		GetClientRect(hWnd, &r);

		SetBkMode(h_dc, TRANSPARENT);
		SetTextColor(h_dc, RGB(255, 255, 0));


		HGDIOBJ h_old_font = SelectObject(h_dc, gh_font);

		//TextOut(h_dc, 10, 10, g_time_str, g_time_len);
		DrawText(h_dc, g_time_str, g_time_len, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		SelectObject(h_dc, h_old_font);
		

		EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_CREATE) {
		SetTimer(hWnd, 1, 1000, NULL);
		gh_font = CreateFont(80, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"굴림체");
		return 0;
	}
	else if (uMsg == WM_TIMER) {
		if (wParam == 1) {
			SYSTEMTIME cur_time;
			GetLocalTime(&cur_time);
			// GetSystemTime();		// UTC로 시간을 받음 / 우리나라시간 UTC + 9

			g_time_len = wsprintf(g_time_str, L"%02d시 %02d분 %02d초", cur_time.wHour, cur_time.wMinute, cur_time.wSecond);
			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
	else if (uMsg == WM_DESTROY) {
		KillTimer(hWnd, 1);
		DeleteObject(gh_font);
		PostQuitMessage(0);
	}
		

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;

	wchar_t my_class_name[] = L"tipssoft";

	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);//COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = my_class_name;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(my_class_name, L"www.tipssoft.com",
		WS_OVERLAPPEDWINDOW, 100, 90, 400, 350, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}