#pragma once
#include <Windows.h>

class HDL_Window
{
public:
	/// <summary>
	/// �A�v���P�[�V�����X�^�[�g�A�f�t�H���g�𑜓x��FHD�A�A�C�R���Ȃ�
	/// </summary>
	/// <param name="WINDOW_WIDTH"> �E�B���h�E�̕�			</param>
	/// <param name="WINDOW_HEIGHT">�E�B���h�E�̍���		</param>
	/// <param name="APP_NAME">		�A�v���P�[�V�����̖��O	</param>
	HDL_Window(const LONG WINDOW_WIDTH = 1920, const LONG WINDOW_HEIGHT = 1080, LPCWSTR appName = L"No Name", LPCWSTR className = L"No Name");

	/// <summary>
	/// OS����̃��b�Z�[�W���Ď����A�I�����b�Z�[�W��������False��Ԃ�
	/// </summary>
	bool ObserveMSG();

	/// <summary>
	/// �E�B���h�E�����
	/// </summary>
	void CloseWindow();

	/// <summary>
	/// HWND��Ԃ�
	/// </summary>
	/// <returns>HWND mHwnd�̎Q��</returns>
	const HWND& GetWindowHandler() { return mHwnd; }

private:
	void GenerateWindow(LPCWSTR appName);

private:
	WNDCLASSEX mWndClass = {};
	HWND	   mHwnd	 = {};
	RECT	   mRect	 = {};
	MSG		   mMsg		 = {};
};

