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

	assert(SUCCEEDED(result));

	GetHandle();
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

	assert(SUCCEEDED(result));
	
	GetHandle();
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

	assert(SUCCEEDED(result));
	
	GetHandle();
}

HDL_DescriptorHeap::~HDL_DescriptorHeap()
{
	mDescHeap.Reset();
}

void HDL_DescriptorHeap::GetHandle()
{
	auto descHeap = mDescHeap.Get();

	mHeapHandle_CPU = descHeap->GetCPUDescriptorHandleForHeapStart();
	mHeapHandle_GPU = descHeap->GetGPUDescriptorHandleForHeapStart();
}
