#pragma once
#include "CommonDX12Header.h"

class HDL_IndexBuffer
{
public:
	/// <summary>
	/// HDL_IndexBufferの初期化
	/// </summary>
	/// <param name="bufferSize">	IndexBufferのサイズ	</param>
	HDL_IndexBuffer(UINT64 bufferSize);

	/// <summary>
	/// IndexBufferをVRAMへコピーする
	/// </summary>
	/// <param name="pIndices">	インデックス配列のアドレス	</param>
	void CopyBufferToVRAM(void* pIndices);

	~HDL_IndexBuffer();

	/// <summary>
	/// IndexBufferViewのアドレスを返す
	/// </summary>
	/// <returns>	D3D12_INDEX_BUFFER_VIEW mIBV	</returns>
	D3D12_INDEX_BUFFER_VIEW* GetView() { return &mIBV; }

private:
	D3D12_INDEX_BUFFER_VIEW mIBV = {};

	ID3D12Device*		   pDevice		= nullptr;
	ComPtr<ID3D12Resource> mIndexBuffer = nullptr;
};

