#pragma once
#ifdef _DEBUG
#include <iostream>
#endif

//DirectInput
#define DIRECTINPUT_VERSION 0x0800
#define KEY_MAX 256
#include "dinput.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class HDL_Input
{
public:
	/// <summary>
	/// Inputクラスを初期化
	/// </summary>
	/// <param name="hwnd">	HWNDを引数にとる	</param>
	HDL_Input(HWND hwnd);

	/// <summary>
	/// キー入力を受け付け、押している間trueを返す
	/// </summary>
	/// <param name="KeyCode">		</param>
	/// <returns>	True / False	</returns>
	bool GetKey(UINT KeyCode);

	~HDL_Input();

private:
	LPDIRECTINPUT8		 pInput  = nullptr;
	LPDIRECTINPUTDEVICE8 pDevice = nullptr;
	BYTE mKeys[KEY_MAX];
};

