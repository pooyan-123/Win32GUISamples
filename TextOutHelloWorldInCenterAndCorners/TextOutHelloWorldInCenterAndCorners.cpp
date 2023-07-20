#include <windows.h>
#include <tchar.h>

#define HELLO_WORLD TEXT("Hello World!")
#define HELLO_WORLD_SIZE 12

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc = { 0 };
	HWND hWnd;
	BOOL bRet;
	MSG msg;

	wc.lpszClassName = TEXT("MyClass");
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hInstance = hInstance;
	if (!RegisterClass(&wc))
		return 0;

	hWnd = CreateWindow(TEXT("MYCLASS"), TEXT("TextOutHelloWorldInCenterAndCorners"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
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
	PAINTSTRUCT ps;
	RECT rcClient;

	switch (message)
	{
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rcClient);
		SetTextAlign(hDC, TA_LEFT | TA_TOP);
		TextOut(hDC, 0, 0, HELLO_WORLD, HELLO_WORLD_SIZE);
		SetTextAlign(hDC, TA_LEFT | TA_BOTTOM);
		TextOut(hDC, 0, rcClient.bottom, HELLO_WORLD, HELLO_WORLD_SIZE);
		SetTextAlign(hDC, TA_RIGHT | TA_TOP);
		TextOut(hDC, rcClient.right, 0, HELLO_WORLD, HELLO_WORLD_SIZE);
		SetTextAlign(hDC, TA_RIGHT | TA_BOTTOM);
		TextOut(hDC, rcClient.right, rcClient.bottom, HELLO_WORLD, HELLO_WORLD_SIZE);
		SetTextAlign(hDC, TA_CENTER | TA_BASELINE);
		TextOut(hDC, rcClient.right / 2, rcClient.bottom / 2, HELLO_WORLD, HELLO_WORLD_SIZE);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}