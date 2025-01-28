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

	~HDL_BackBuffer();

private:
	D3D12_VIEWPORT mViewPort    = {};
	D3D12_RECT     mScissorRect = {};

	class HDL_DescriptorHeap* pRTVDescHeap  = nullptr;
	class HDL_Renderer*		  pRenderer     = nullptr;
	std::vector<ComPtr<ID3D12Resource>> mBackBuffers;
};

