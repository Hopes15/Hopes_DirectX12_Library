#pragma once
#include "CommonDX12Header.h"

//DXGI
#include <dxgi1_6.h>
#pragma comment(lib, "dxgi.lib")

class HDL_Renderer
{
	//�V���O���g��
public:
	/// <summary>
	/// HDL_Renderer�N���X�̃C���X�^���X���擾
	/// </summary>
	/// <returns>	pInstance (DX12*)	</returns>
	static HDL_Renderer* GetInstance()
	{
		return pInstance;
	}

	/// <summary>
	/// HDL_Renderer�N���X��������
	/// </summary>
	/// <param name="WIDTH">	Window�̕�					</param>
	/// <param name="HEIGHT">	Window�̍���				</param>
	/// <param name="hwnd">		WindowHandler�̃C���X�^���X	</param>
	static void Create(UINT WIDTH, UINT HEIGHT, HWND hwnd)
	{
		if (!pInstance) pInstance = new HDL_Renderer(WIDTH, HEIGHT, hwnd);
	}

	/// <summary>
	/// HDL_Renderer�N���X�̃C���X�^���X��j��
	/// </summary>
	static void Destroy()
	{
		delete pInstance;
		pInstance = nullptr;
	}

private:
	static HDL_Renderer* pInstance;

	HDL_Renderer(UINT WIDTH, UINT HEIGHT, HWND hwnd);
	~HDL_Renderer();

public:
	/// <summary>
	/// �`�揀������
	/// </summary>
	void EnterDrawing();

	/// <summary>
	/// �`��I������
	/// </summary>
	void ExitDrawing();

	/// <summary>
	/// �f�o�C�X�N���X�̃|�C���^�[��Ԃ�
	/// </summary>
	/// <returns>	ID3D12Device*	</returns>
	ID3D12Device* GetDevice() { return mDevice.Get(); }

	/// <summary>
	/// �R�}���h���X�g�̃|�C���^�[��Ԃ�
	/// </summary>
	/// <returns>	ID3D12GraphicsCommandList*	</returns>
	ID3D12GraphicsCommandList* GetCmdList() { return mCmdList.Get(); }

	/// <summary>
	/// �X���b�v�`�F�[���S�̃|�C���^�[��Ԃ�
	/// </summary>
	/// <returns>	IDXGISwapChain4*	</returns>
	IDXGISwapChain4* GetSwapChain4() { return mSwapChain4.Get(); }

private:
	//Create�֐�
	bool CreateFactory();
	bool CreateDevice();
	bool CreateCmdAllocator();
	bool CreateCmdList();
	bool CreateCmdQueue();
	bool CreateSwapChain();
	bool CreateFence();

	//Draw�֘A
	void WaitDrawing();

public:
	const UINT WINDOW_WIDTH;
	const UINT WINDOW_HEIGHT;
	const UINT BUFFER_COUNT;

private:
	UINT64 mFenceVal;
	HWND   mHWND = {};

	ComPtr<IDXGIFactory6>				mFactory		= nullptr;
	ComPtr<IDXGIAdapter>				mAdapter		= nullptr;
	ComPtr<ID3D12Device>				mDevice			= nullptr;
	ComPtr<ID3D12CommandAllocator>		mCmdAllocator	= nullptr;
	ComPtr<ID3D12GraphicsCommandList>	mCmdList		= nullptr;
	ComPtr<ID3D12CommandQueue>		    mCmdQueue		= nullptr;
	ComPtr<IDXGISwapChain4>			    mSwapChain4		= nullptr;
	ComPtr<ID3D12Fence>					mFence			= nullptr;
};


