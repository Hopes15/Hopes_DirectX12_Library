#pragma once
#include "CommonDX12Header.h"

class HDL_VertexBuffer
{
public:
	/// <summary>
	/// HDL_VertexBuffer�̏�����
	/// </summary>
	/// <param name="bufferSize">	VertexBuffer�̃T�C�Y	</param>
	/// <param name="stride">		�P���_�̃T�C�Y			</param>
	HDL_VertexBuffer(UINT64 bufferSize, UINT stride);

	/// <summary>
	/// VertexBuffer��VRAM�փR�s�[����
	/// </summary>
	/// <param name="pVertices">	���_�z��̃A�h���X	</param>
	void CopyBufferToVRAM(void* pVertices);

	~HDL_VertexBuffer();

	/// <summary>
	/// VertexBufferView�̃A�h���X��Ԃ�
	/// </summary>
	/// <returns>	D3D12_VERTEX_BUFFER_VIEW mVBV	</returns>
	D3D12_VERTEX_BUFFER_VIEW* GetView() { return &mVBV; }

private:
	D3D12_VERTEX_BUFFER_VIEW mVBV = {};

	ID3D12Device*		   pDevice	   = nullptr;
	ComPtr<ID3D12Resource> mVertexBuff = nullptr;
};

