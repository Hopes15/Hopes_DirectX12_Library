#pragma once
#include <cassert>

//DirectInput
#define DIRECTINPUT_VERSION 0x0800
#define KEY_MAX 256
#include "dinput.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

/// <summary>
/// �V���O���g���N���X�iCreate()�Ăяo���K�{�j
/// </summary>
class HDL_Input
{
	//�V���O���g��
public:
	/// <summary>
	/// HDL_Input�N���X�̃C���X�^���X���擾
	/// </summary>
	/// <returns></returns>
	static HDL_Input* GetInstance() { return pInstance; }

	/// <summary>
	/// �C���X�^���X����
	/// </summary>
	/// <param name="hwnd"></param>
	static void Create(HWND hwnd)
	{
		if (!pInstance) pInstance = new HDL_Input(hwnd);
	}

	/// <summary>
	/// �C���X�^���X�j��
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
	/// �L�[���͂��󂯕t���A�����Ă����true��Ԃ�
	/// </summary>
	/// <param name="KeyCode">		</param>
	/// <returns>	True / False	</returns>
	bool GetKey(UINT KeyCode);

private:
	LPDIRECTINPUT8		 pInput  = nullptr;
	LPDIRECTINPUTDEVICE8 pDevice = nullptr;
	BYTE mKeys[KEY_MAX];
};

