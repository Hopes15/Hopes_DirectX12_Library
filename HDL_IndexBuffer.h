#pragma once
#include "CommonDX12Header.h"

class HDL_IndexBuffer
{
public:
	/// <summary>
	/// HDL_IndexBuffer�̏�����
	/// </summary>
	/// <param name="bufferSize">	IndexBuffer�̃T�C�Y	</param>
	HDL_IndexBuffer(UINT64 bufferSize);

	/// <summary>
	/// IndexBuffer��VRAM�փR�s�[����
	/// </summary>
	/// <param name="pIndices">	�C���f�b�N�X�z��̃A�h���X	</param>
	void CopyBufferToVRAM(void* pIndices);

	~HDL_IndexBuffer();

	/// <summary>
	/// IndexBufferView�̃A�h���X��Ԃ�
	/// </summary>
	/// <returns>	D3D12_INDEX_BUFFER_VIEW mIBV	</returns>
	D3D12_INDEX_BUFFER_VIEW* GetView() { return &mIBV; }

private:
	D3D12_INDEX_BUFFER_VIEW mIBV = {};

	ID3D12Device*		   pDevice		= nullptr;
	ComPtr<ID3D12Resource> mIndexBuffer = nullptr;
};

