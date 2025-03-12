#include "HDL_Input.h"

HDL_Input::HDL_Input(HWND hwnd)
{
	//初期化
	memset(&mKeys, 0, sizeof(mKeys));

	//DirectInputを作成
	auto result = DirectInput8Create(
		/*HINSTANCE*/ GetModuleHandle(0),
		/*Version  */ DIRECTINPUT_VERSION,
		/*IID	   */ IID_IDirectInput8,
		/*ppvOut   */ (void**)&pInput,
		/*punkOuter*/ NULL
	);

	assert(SUCCEEDED(result));

	//Divice(Key)を作成
	result = pInput->CreateDevice(
		/*GUID				  */ GUID_SysKeyboard,
		/*LPDIRECTINPUTDEVICE8*/ &pDevice,
		/*LPUNKNOWN			  */ NULL
	);

	assert(SUCCEEDED(result));

	//DeviceをFormat
	result = pDevice->SetDataFormat(&c_dfDIKeyboard);

	assert(SUCCEEDED(result));

	//Deviceの設定
	result = pDevice->SetCooperativeLevel(
		hwnd,
		DISCL_NONEXCLUSIVE | DISCL_BACKGROUND
	);

	assert(SUCCEEDED(result));

	//入力受付
	pDevice->Acquire();
}

bool HDL_Input::GetKey(UINT KeyCode)
{
	// キーボード状態の取得
	pDevice->GetDeviceState(sizeof(mKeys), (LPVOID)&mKeys);

	if (mKeys[KeyCode] & 0x80) return true;
	else					   return false;
}

HDL_Input::~HDL_Input()
{
	pDevice->Unacquire();
	pDevice->Release();
	pInput ->Release();
}