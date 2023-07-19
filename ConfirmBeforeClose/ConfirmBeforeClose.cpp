#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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

	hWnd = CreateWindow(TEXT("MyClass"), TEXT("ConfirmBeforeClose"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
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
	int iRes;

	switch (message)
	{
	case WM_CLOSE:
		iRes = MessageBox(hWnd, TEXT("Do you really want to close the window?"), TEXT("Close"), MB_YESNO | MB_ICONEXCLAMATION);
		if (iRes == IDYES)
			DestroyWindow(hWnd);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}