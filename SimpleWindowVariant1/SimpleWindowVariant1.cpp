#include <windows.h>
#include <tchar.h>

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	WNDCLASS wndclass;
	BOOL bRet;
	MSG msg;

	wndclass.lpszClassName = TEXT("MyClass");
	wndclass.lpfnWndProc = DefWindowProc;
	wndclass.style = 0;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpszMenuName = NULL;
	wndclass.hInstance = hInstance;
	if (!RegisterClass(&wndclass))
		return 0;

	hWnd = CreateWindow(TEXT("MyClass"), TEXT("SimpleWindow"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
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