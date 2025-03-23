#include "HDL_Window.h"

LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (msg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}

HDL_Window::HDL_Window(const LONG WINDOW_WIDTH, const LONG WINDOW_HEIGHT, LPCWSTR appName, LPCWSTR className)
{
	//ウィンドウクラスの定義
	mWndClass.cbSize		= sizeof(WNDCLASSEX);
	mWndClass.lpfnWndProc	= (WNDPROC)WindowProcedure;
	mWndClass.lpszClassName = className;
	mWndClass.hInstance		= GetModuleHandle(nullptr);

	RegisterClassEx(&mWndClass);

	//サイズ調整
	mRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&mRect, WS_OVERLAPPEDWINDOW, false);

	GenerateWindow(appName);
}

void HDL_Window::GenerateWindow(LPCWSTR appName)
{
	//ウィンドウオブジェクトの生成
	mHwnd = CreateWindow(
		mWndClass.lpszClassName,
		appName,
		WS_OVERLAPPED | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		mRect.right  - mRect.left,
		mRect.bottom - mRect.top,
		nullptr,
		nullptr,
		mWndClass.hInstance,
		nullptr
	);

	//ウィンドウを表示
	ShowWindow(mHwnd, SW_SHOW);
}

bool HDL_Window::ObserveMSG()
{
	while (mMsg.message != WM_QUIT)
	{
		if (PeekMessage(&mMsg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&mMsg);
			DispatchMessage(&mMsg);
		}
		else
		{
			break;
		}
	}

	return mMsg.message != WM_QUIT;
}

void HDL_Window::CloseWindow()
{
	//登録解除
	UnregisterClass(mWndClass.lpszClassName, mWndClass.hInstance);
}