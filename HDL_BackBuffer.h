#pragma once
#include "CommonDX12Header.h"

class HDL_BackBuffer
{
public:
	HDL_BackBuffer();

	/// <summary>
	/// バックバッファーへの描画準備処理
	/// </summary>
	/// <param name="clearColor">	画面クリアをする色 float[] = (R, G, B, A)	</param>
	void OpenBackBuffer(const float* clearColor);

	/// <summary>
	/// バックバッファーへの描画終了処理
	/// </summary>
	void CloseBackBuffer();

	/// <summary>
	/// ディスクリプタヒープのヒープハンドルを取得
	/// </summary>
	/// <returns></returns>
	D3D12_CPU_DESCRIPTOR_HANDLE* GetHeapHandle() { return &mHeapHandle; }

	~HDL_BackBuffer();

private:
	D3D12_VIEWPORT				mViewPort    = {};
	D3D12_RECT					mScissorRect = {};
	D3D12_CPU_DESCRIPTOR_HANDLE mHeapHandle  = {};

	class HDL_DescriptorHeap* pRTVDescHeap  = nullptr;
	class HDL_Renderer*		  pRenderer     = nullptr;
	std::vector<ComPtr<ID3D12Resource>> mBackBuffers;
};

