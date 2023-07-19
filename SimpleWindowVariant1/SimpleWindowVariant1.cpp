#include <windows.h>
#include <tchar.h>

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc = { 0 };
	HWND hWnd;
	BOOL bRet;
	MSG msg;

	wc.lpszClassName = TEXT("MyClass");
	wc.lpfnWndProc = DefWindowProc;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hInstance = hInstance;
	if (!RegisterClass(&wc))
		return 0;

	hWnd = CreateWindow(TEXT("MyClass"), TEXT("SimpleWindowVariant1"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	if (!hWnd)
		return 0;

	ShowWindow(hWnd, nCmdShow);
	if (!UpdateWindow(hWnd))
		return 0;

	while ((bRet = GetMessage(&msg, hWnd, 0, 0)) != 0)
	{
		if (bRet == -1)
			return 0;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}