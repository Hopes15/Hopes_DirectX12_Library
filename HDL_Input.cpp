#include "HDL_Input.h"

HDL_Input::HDL_Input(HWND hwnd)
{
	//������
	memset(&mKeys, 0, sizeof(mKeys));

	//DirectInput���쐬
	auto result = DirectInput8Create(
		/*HINSTANCE*/ GetModuleHandle(0),
		/*Version  */ DIRECTINPUT_VERSION,
		/*IID	   */ IID_IDirectInput8,
		/*ppvOut   */ (void**)&pInput,
		/*punkOuter*/ NULL
	);

	assert(SUCCEEDED(result));

	//Divice(Key)���쐬
	result = pInput->CreateDevice(
		/*GUID				  */ GUID_SysKeyboard,
		/*LPDIRECTINPUTDEVICE8*/ &pDevice,
		/*LPUNKNOWN			  */ NULL
	);

	assert(SUCCEEDED(result));

	//Device��Format
	result = pDevice->SetDataFormat(&c_dfDIKeyboard);

	assert(SUCCEEDED(result));

	//Device�̐ݒ�
	result = pDevice->SetCooperativeLevel(
		hwnd,
		DISCL_NONEXCLUSIVE | DISCL_BACKGROUND
	);

	assert(SUCCEEDED(result));

	//���͎�t
	pDevice->Acquire();
}

bool HDL_Input::GetKey(UINT KeyCode)
{
	// �L�[�{�[�h��Ԃ̎擾
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