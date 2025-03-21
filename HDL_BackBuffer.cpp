#include "HDL_BackBuffer.h"
#include "HDL_Renderer.h"
#include "HDL_DescriptorHeap.h"

HDL_BackBuffer::HDL_BackBuffer() : pRenderer(HDL_Renderer::GetInstance())
{
	//DescriptorHeapを作成
	pRTVDescHeap = new HDL_DescriptorHeap();
	pRTVDescHeap->CreateAsRTV(pRenderer->BUFFER_COUNT);

	////sRGB用
	//D3D12_RENDER_TARGET_VIEW_DESC RTVdesc = {};
	//RTVdesc.Format			= DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	//RTVdesc.ViewDimension	= D3D12_RTV_DIMENSION_TEXTURE2D;

	//RTVの生成
	//バックバッファの数分リソースを用意
	mBackBuffers.resize(pRenderer->BUFFER_COUNT);
	mHeapHandle = pRTVDescHeap->GetPointerOfDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();

	for (UINT i = 0; i < pRenderer->BUFFER_COUNT; ++i)
	{
		//バッファー取得
		auto result = pRenderer->GetSwapChain4()->GetBuffer(i, IID_PPV_ARGS(mBackBuffers[i].ReleaseAndGetAddressOf()));
		assert(SUCCEEDED(result));
		
		//RTV生成
		pRenderer->GetDevice()->CreateRenderTargetView(mBackBuffers[i].Get(), nullptr, mHeapHandle);
		//ポインターをずらす
		mHeapHandle.ptr += pRenderer->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}

	//ビューポートの設定
	mViewPort.Width		= static_cast<FLOAT>(pRenderer->WINDOW_WIDTH);
	mViewPort.Height	= static_cast<FLOAT>(pRenderer->WINDOW_HEIGHT);
	mViewPort.TopLeftX	= 0;
	mViewPort.TopLeftY	= 0;
	mViewPort.MaxDepth	= 1.0f;
	mViewPort.MinDepth	= 0.0f;

	//シザー矩形の設定
	mScissorRect.left	= 0;
	mScissorRect.top	= 0;
	mScissorRect.right	= mScissorRect.left + pRenderer->WINDOW_WIDTH;
	mScissorRect.bottom = mScissorRect.top  + pRenderer->WINDOW_HEIGHT;
}

void HDL_BackBuffer::OpenBackBuffer(const float* clearColor)
{
	auto cmdList	 = pRenderer->GetCmdList();
	auto backBuffIdx = pRenderer->GetSwapChain4()->GetCurrentBackBufferIndex();

	//リソースバリア
	auto transition = CD3DX12_RESOURCE_BARRIER::Transition(
		/*pResouce*/ mBackBuffers[backBuffIdx].Get(),
		/*Before  */ D3D12_RESOURCE_STATE_PRESENT,
		/*After   */ D3D12_RESOURCE_STATE_RENDER_TARGET
	);
	cmdList->ResourceBarrier(1, &transition);

	//レンダーターゲット
	mHeapHandle = pRTVDescHeap->GetPointerOfDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();
	mHeapHandle.ptr += backBuffIdx * pRenderer->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	//レンダーターゲットをクリア
	cmdList->ClearRenderTargetView(mHeapHandle, clearColor, 0, nullptr);

	//ビューポート・シザー矩形をセット
	cmdList->RSSetViewports(1, &mViewPort);
	cmdList->RSSetScissorRects(1, &mScissorRect);
}

void HDL_BackBuffer::CloseBackBuffer()
{
	auto cmdList	 = pRenderer->GetCmdList();
	auto backBuffIdx = pRenderer->GetSwapChain4()->GetCurrentBackBufferIndex();

	//リソースバリア
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