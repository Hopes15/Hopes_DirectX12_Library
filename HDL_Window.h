#pragma once
#include <Windows.h>

class HDL_Window
{
public:
	/// <summary>
	/// アプリケーションスタート、デフォルト解像度はFHD、アイコンなし
	/// </summary>
	/// <param name="WINDOW_WIDTH"> ウィンドウの幅			</param>
	/// <param name="WINDOW_HEIGHT">ウィンドウの高さ		</param>
	/// <param name="APP_NAME">		アプリケーションの名前	</param>
	HDL_Window(const LONG WINDOW_WIDTH = 1920, const LONG WINDOW_HEIGHT = 1080, LPCWSTR appName = L"No Name", LPCWSTR className = L"No Name");

	/// <summary>
	/// OSからのメッセージを監視し、終了メッセージが来たらFalseを返す
	/// </summary>
	bool ObserveMSG();

	/// <summary>
	/// ウィンドウを閉じる
	/// </summary>
	void CloseWindow();

	/// <summary>
	/// HWNDを返す
	/// </summary>
	/// <returns>HWND mHwndの参照</returns>
	const HWND& GetWindowHandler() { return mHwnd; }

private:
	void GenerateWindow(LPCWSTR appName);

private:
	WNDCLASSEX mWndClass = {};
	HWND	   mHwnd	 = {};
	RECT	   mRect	 = {};
	MSG		   mMsg		 = {};
};

