#pragma once
#include "CommonDX12Header.h"

class HDL_BackBuffer
{
public:
	HDL_BackBuffer();

	/// <summary>
	/// �o�b�N�o�b�t�@�[�ւ̕`�揀������
	/// </summary>
	/// <param name="clearColor">	��ʃN���A������F float[] = (R, G, B, A)	</param>
	void OpenBackBuffer(const float* clearColor);

	/// <summary>
	/// �o�b�N�o�b�t�@�[�ւ̕`��I������
	/// </summary>
	void CloseBackBuffer();

	/// <summary>
	/// �f�B�X�N���v�^�q�[�v�̃q�[�v�n���h�����擾
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

