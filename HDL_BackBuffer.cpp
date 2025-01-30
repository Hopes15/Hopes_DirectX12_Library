#include "HDL_BackBuffer.h"
#include "HDL_Renderer.h"
#include "HDL_DescriptorHeap.h"

HDL_BackBuffer::HDL_BackBuffer() : pRenderer(HDL_Renderer::GetInstance())
{
	//DescriptorHeap���쐬
	pRTVDescHeap = new HDL_DescriptorHeap();
	pRTVDescHeap->CreateAsRTV(pRenderer->BUFFER_COUNT);

	////sRGB�p
	//D3D12_RENDER_TARGET_VIEW_DESC RTVdesc = {};
	//RTVdesc.Format			= DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	//RTVdesc.ViewDimension	= D3D12_RTV_DIMENSION_TEXTURE2D;

	//RTV�̐���
	//�o�b�N�o�b�t�@�̐������\�[�X��p��
	mBackBuffers.resize(pRenderer->BUFFER_COUNT);
	auto handle = pRTVDescHeap->GetPointerOfDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();

	for (UINT i = 0; i < pRenderer->BUFFER_COUNT; ++i)
	{
		//�o�b�t�@�[�擾
		auto result = pRenderer->GetSwapChain4()->GetBuffer(i, IID_PPV_ARGS(mBackBuffers[i].ReleaseAndGetAddressOf()));

		if (FAILED(result))
		{
#ifdef _DEBUG
			std::cout << "BackBuffer(ID3D12Resource)�̐����Ɏ��s" << std::endl;
#endif
		}
		//RTV����
		pRenderer->GetDevice()->CreateRenderTargetView(mBackBuffers[i].Get(), nullptr, handle);
		//�|�C���^�[�����炷
		handle.ptr += pRenderer->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}

	//�r���[�|�[�g�̐ݒ�
	mViewPort.Width		= static_cast<FLOAT>(pRenderer->WINDOW_WIDTH);
	mViewPort.Height	= static_cast<FLOAT>(pRenderer->WINDOW_HEIGHT);
	mViewPort.TopLeftX	= 0;
	mViewPort.TopLeftY	= 0;
	mViewPort.MaxDepth	= 1.0f;
	mViewPort.MinDepth	= 0.0f;

	//�V�U�[��`�̐ݒ�
	mScissorRect.left	= 0;
	mScissorRect.top	= 0;
	mScissorRect.right	= mScissorRect.left + pRenderer->WINDOW_WIDTH;
	mScissorRect.bottom = mScissorRect.top  + pRenderer->WINDOW_HEIGHT;
}

void HDL_BackBuffer::OpenBackBuffer(const float* clearColor)
{
	auto cmdList	 = pRenderer->GetCmdList();
	auto backBuffIdx = pRenderer->GetSwapChain4()->GetCurrentBackBufferIndex();

	//���\�[�X�o���A
	auto transition = CD3DX12_RESOURCE_BARRIER::Transition(
		/*pResouce*/ mBackBuffers[backBuffIdx].Get(),
		/*Before  */ D3D12_RESOURCE_STATE_PRESENT,
		/*After   */ D3D12_RESOURCE_STATE_RENDER_TARGET
	);
	cmdList->ResourceBarrier(1, &transition);

	//�����_�[�^�[�Q�b�g
	auto RTVHandler = pRTVDescHeap->GetPointerOfDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();
	RTVHandler.ptr += backBuffIdx * pRenderer->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	//�����_�[�^�[�Q�b�g���Z�b�g
	cmdList->OMSetRenderTargets(1, &RTVHandler, false, nullptr);

	//�����_�[�^�[�Q�b�g���N���A
	cmdList->ClearRenderTargetView(RTVHandler, clearColor, 0, nullptr);

	//�r���[�|�[�g�E�V�U�[��`���Z�b�g
	cmdList->RSSetViewports(1, &mViewPort);
	cmdList->RSSetScissorRects(1, &mScissorRect);
}

void HDL_BackBuffer::CloseBackBuffer()
{
	auto cmdList	 = pRenderer->GetCmdList();
	auto backBuffIdx = pRenderer->GetSwapChain4()->GetCurrentBackBufferIndex();

	//���\�[�X�o���A
	auto transition = CD3DX12_RESOURCE_BARRIER::Transition(
		/*pResouce*/ mBackBuffers[backBuffIdx].Get(),
		/*Before  */ D3D12_RESOURCE_STATE_RENDER_TARGET,
		/*After   */ D3D12_RESOURCE_STATE_PRESENT
	);
	cmdList->ResourceBarrier(1, &transition);
}

HDL_BackBuffer::~HDL_BackBuffer()
{
	for (auto& backBuff : mBackBuffers) backBuff.Reset();
	delete pRTVDescHeap;
}