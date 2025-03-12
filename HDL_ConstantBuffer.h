#pragma once
#include "CommonDX12Header.h"

class HDL_ConstantBuffer
{
public:
	/// <summary>
	/// HDL_ConstantBufferクラスを初期化
	/// </summary>
	/// <param name="bufferSize">	ConstantBufferのサイズ					</param>
	/// <param name="handle">		DescriptorHeapのハンドル（ポインタ）	</param>
	HDL_ConstantBuffer(UINT64 bufferSize, D3D12_CPU_DESCRIPTOR_HANDLE handle);

	/// <summary>
	/// ConstantBufferをVRAMへコピーする
	/// </summary>
	/// <param name="pSomeThing">	コンスタントバッファーに確保する何か	</param>
	void CopyBufferToVRAM(void* pSomeThing);

	/// <summary>
	/// ConstantBufferの内容を更新する
	/// </summary>
	/// <param name="pSomeThing">	コンスタントバッファーに確保する何か	</param>
	void UpdateCBuffer(void* pSomeThing);

	~HDL_ConstantBuffer();

private:
	D3D12_CONSTANT_BUFFER_VIEW_DESC mCBV = {};

	void*				   pMappedSomeThing = nullptr;
	ID3D12Device*		   pDevice		    = nullptr;
	ComPtr<ID3D12Resource> mConstantBuff	= nullptr;
};

