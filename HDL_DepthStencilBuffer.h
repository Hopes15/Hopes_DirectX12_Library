#pragma once
#include "CommonDX12Header.h"

class HDL_DepthStencilBuffer
{
public:
	HDL_DepthStencilBuffer();

	~HDL_DepthStencilBuffer();

	void OpenDSBuffer();

	/// <summary>
	/// ディスクリプタヒープのヒープハンドルを取得
	/// </summary>
	/// <returns></returns>
	inline D3D12_CPU_DESCRIPTOR_HANDLE* GetHeapHandle() { return &mHeapHandle; }

private:
	D3D12_CPU_DESCRIPTOR_HANDLE mHeapHandle = {};

	class HDL_DescriptorHeap* pDSVDescHeap = nullptr;
	class HDL_Renderer*		  pRenderer	   = nullptr;
	ComPtr<ID3D12Resource>	  mDSBuff	   = nullptr;
};

