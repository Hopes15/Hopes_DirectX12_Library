#include "HDL_DepthStencilBuffer.h"
#include "HDL_Renderer.h"
#include "HDL_DescriptorHeap.h"

HDL_DepthStencilBuffer::HDL_DepthStencilBuffer() : 
	pRenderer(HDL_Renderer::GetInstance())
{
	auto dev = pRenderer->GetDevice();

	//DescriptorHeapの作成
	pDSVDescHeap = new HDL_DescriptorHeap();
	pDSVDescHeap->CreateAsDSV(1);

	//リソース作成
	auto heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	auto resDesc  = CD3DX12_RESOURCE_DESC(
		/*Resource Dimension*/ D3D12_RESOURCE_DIMENSION_TEXTURE2D,
		/*Alignment			*/ 0,
		/*Width				*/ pRenderer->WINDOW_WIDTH,
		/*Height			*/ pRenderer->WINDOW_HEIGHT,
		/*DepthOrArraySize	*/ 1,
		/*MipLevels			*/ 1,
		/*Format			*/ DXGI_FORMAT_D32_FLOAT,
		/*SampleCount		*/ 1,
		/*SampleQuality		*/ 0,
		/*Texture Layout	*/ D3D12_TEXTURE_LAYOUT_UNKNOWN,
		/*Resource Flags	*/ D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL
	);

	//クリアバリュー
	CD3DX12_CLEAR_VALUE depthClearValue(DXGI_FORMAT_D32_FLOAT, 1.0f, 0);

	auto result = dev->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&depthClearValue,
		IID_PPV_ARGS(mDSBuff.ReleaseAndGetAddressOf())
	);

	if (FAILED(result)) {
#ifdef _DEBUG
		std::cout << "Depth Stencil Bufferの生成に失敗" << std::endl;
#endif
		return;
	}

	//DSVの作成
	D3D12_DEPTH_STENCIL_VIEW_DESC DSVDesc = {};
	DSVDesc.Format		  = DXGI_FORMAT_D32_FLOAT;
	DSVDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	DSVDesc.Flags		  = D3D12_DSV_FLAG_NONE;

	mHeapHandle = pDSVDescHeap->GetPointerOfDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();
	dev->CreateDepthStencilView(mDSBuff.Get(), &DSVDesc, mHeapHandle);
}

HDL_DepthStencilBuffer::~HDL_DepthStencilBuffer()
{
	mDSBuff.Reset();
	delete pDSVDescHeap;
}

void HDL_DepthStencilBuffer::OpenDSBuffer()
{
	//Get CmdList
	auto cmdList = pRenderer->GetCmdList();

	//Clear View
	cmdList->ClearDepthStencilView(mHeapHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}
