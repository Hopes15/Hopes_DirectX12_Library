#pragma once
#include "CommonDX12Header.h"

class HDL_VertexBuffer
{
public:
	/// <summary>
	/// HDL_VertexBufferの初期化
	/// </summary>
	/// <param name="bufferSize">	VertexBufferのサイズ	</param>
	/// <param name="stride">		１頂点のサイズ			</param>
	HDL_VertexBuffer(UINT64 bufferSize, UINT stride);

	/// <summary>
	/// VertexBufferをVRAMへコピーする
	/// </summary>
	/// <param name="pVertices">	頂点配列のアドレス	</param>
	void CopyBufferToVRAM(void* pVertices);

	~HDL_VertexBuffer();

	/// <summary>
	/// VertexBufferViewのアドレスを返す
	/// </summary>
	/// <returns>	D3D12_VERTEX_BUFFER_VIEW mVBV	</returns>
	D3D12_VERTEX_BUFFER_VIEW* GetView() { return &mVBV; }

private:
	D3D12_VERTEX_BUFFER_VIEW mVBV = {};

	ID3D12Device*		   pDevice	   = nullptr;
	ComPtr<ID3D12Resource> mVertexBuff = nullptr;
};

