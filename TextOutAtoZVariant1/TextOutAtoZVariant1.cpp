#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

const TCHAR szAtoZ[] = TEXT("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc = { 0 };
	HWND hWnd;
	BOOL bRet;
	MSG msg;

	wc.lpszClassName = TEXT("MyClass");
	wc.lpfnWndProc = WndProc;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hInstance = hInstance;
	if (!RegisterClass(&wc))
		return 0;

	hWnd = CreateWindow(TEXT("MYCLASS"), TEXT("TextOutAtoZVariant1"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	if (!hWnd)
		return 0;

	ShowWindow(hWnd, nCmdShow);
	if (!UpdateWindow(hWnd))
		return 0;

	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (bRet == -1)
			return 0;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	TEXTMETRIC tm;
	static LONG cyChar;
	PAINTSTRUCT ps;
	size_t iFirstLineToPaint;
	size_t iLastLineToPaint;
	const size_t iLastLine = (sizeof(szAtoZ) / sizeof(TCHAR)) - 2;

	switch (message)
	{
	case WM_CREATE:
		hDC = GetDC(hWnd);
		if (!GetTextMetrics(hDC, &tm))
			return -1;
		cyChar = tm.tmHeight + tm.tmExternalLeading;
		ReleaseDC(hWnd, hDC);
		return 0;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		iFirstLineToPaint = ps.rcPaint.top / cyChar;
		iLastLineToPaint = min((ps.rcPaint.bottom / cyChar) + 1, iLastLine);
		if (iFirstLineToPaint <= iLastLine)
			for (size_t i = iFirstLineToPaint; i <= iLastLineToPaint; i++)
			{
				TextOut(hDC, 30, i * cyChar, &szAtoZ[i], 1);
			}
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}