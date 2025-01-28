#include "HDL_DescriptorHeap.h"
#include "HDL_Renderer.h"

HDL_DescriptorHeap::HDL_DescriptorHeap() : pDevice(HDL_Renderer::GetInstance()->GetDevice()) {}

void HDL_DescriptorHeap::CreateAsCBV_SRV_UAV(UINT numDescriptors)
{
	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.Type			= D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	desc.NodeMask		= 0;
	desc.NumDescriptors = numDescriptors;
	desc.Flags			 = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

	//ディスクリプタヒープの生成
	auto result = pDevice->CreateDescriptorHeap(
		/*pDescriptorHeapDesc*/ &desc,
		/*ppDescriptorHeap   */ IID_PPV_ARGS(mDescHeap.ReleaseAndGetAddressOf())
	);

	if (FAILED(result))
	{
#ifdef _DEBUG
		std::cout << "ディスクリプタヒープ(CBV_SRV_UAV)の生成に失敗" << std::endl;
#endif
	}
}

void HDL_DescriptorHeap::CreateAsRTV(UINT numDescriptors)
{
	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.Type			= D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	desc.NodeMask		= 0;
	desc.NumDescriptors = numDescriptors;
	desc.Flags			= D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	//ディスクリプタヒープの生成
	auto result = pDevice->CreateDescriptorHeap(
		/*pDescriptorHeapDesc*/ &desc,
		/*ppDescriptorHeap   */ IID_PPV_ARGS(mDescHeap.ReleaseAndGetAddressOf())
	);

	if (FAILED(result))
	{
#ifdef _DEBUG
		std::cout << "ディスクリプタヒープ(RTV)の生成に失敗" << std::endl;
#endif
	}
}

void HDL_DescriptorHeap::CreateAsDSV(UINT numDescriptors)
{
	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.Type			= D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	desc.NodeMask		= 0;
	desc.NumDescriptors = numDescriptors;
	desc.Flags			= D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	//ディスクリプタヒープの生成
	auto result = pDevice->CreateDescriptorHeap(
		/*pDescriptorHeapDesc*/ &desc,
		/*ppDescriptorHeap   */ IID_PPV_ARGS(mDescHeap.ReleaseAndGetAddressOf())
	);

	if (FAILED(result))
	{
#ifdef _DEBUG
		std::cout << "ディスクリプタヒープ(DSV)の生成に失敗" << std::endl;
#endif
	}
}

HDL_DescriptorHeap::~HDL_DescriptorHeap()
{
	mDescHeap.Reset();
}