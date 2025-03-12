#pragma once
#include "CommonDX12Header.h"

class HDL_ConstantBuffer
{
public:
	/// <summary>
	/// HDL_ConstantBuffer�N���X��������
	/// </summary>
	/// <param name="bufferSize">	ConstantBuffer�̃T�C�Y					</param>
	/// <param name="handle">		DescriptorHeap�̃n���h���i�|�C���^�j	</param>
	HDL_ConstantBuffer(UINT64 bufferSize, D3D12_CPU_DESCRIPTOR_HANDLE handle);

	/// <summary>
	/// ConstantBuffer��VRAM�փR�s�[����
	/// </summary>
	/// <param name="pSomeThing">	�R���X�^���g�o�b�t�@�[�Ɋm�ۂ��鉽��	</param>
	void CopyBufferToVRAM(void* pSomeThing);

	/// <summary>
	/// ConstantBuffer�̓��e���X�V����
	/// </summary>
	/// <param name="pSomeThing">	�R���X�^���g�o�b�t�@�[�Ɋm�ۂ��鉽��	</param>
	void UpdateCBuffer(void* pSomeThing);

	~HDL_ConstantBuffer();

private:
	D3D12_CONSTANT_BUFFER_VIEW_DESC mCBV = {};

	void*				   pMappedSomeThing = nullptr;
	ID3D12Device*		   pDevice		    = nullptr;
	ComPtr<ID3D12Resource> mConstantBuff	= nullptr;
};

