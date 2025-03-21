#pragma once
#include <cassert>

//DirectInput
#define DIRECTINPUT_VERSION 0x0800
#define KEY_MAX 256
#include "dinput.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

/// <summary>
/// シングルトンクラス（Create()呼び出し必須）
/// </summary>
class HDL_Input
{
	//シングルトン
public:
	/// <summary>
	/// HDL_Inputクラスのインスタンスを取得
	/// </summary>
	/// <returns></returns>
	static HDL_Input* GetInstance() { return pInstance; }

	/// <summary>
	/// インスタンス生成
	/// </summary>
	/// <param name="hwnd"></param>
	static void Create(HWND hwnd)
	{
		if (!pInstance) pInstance = new HDL_Input(hwnd);
	}

	/// <summary>
	/// インスタンス破棄
	/// </summary>
	static void Destroy()
	{
		delete pInstance;
		pInstance = nullptr;
	}

private:
	static HDL_Input* pInstance;

	HDL_Input(HWND hwnd);
	~HDL_Input();

public:
	/// <summary>
	/// キー入力を受け付け、押している間trueを返す
	/// </summary>
	/// <param name="KeyCode">		</param>
	/// <returns>	True / False	</returns>
	bool GetKey(UINT KeyCode);

private:
	LPDIRECTINPUT8		 pInput  = nullptr;
	LPDIRECTINPUTDEVICE8 pDevice = nullptr;
	BYTE mKeys[KEY_MAX];
};

