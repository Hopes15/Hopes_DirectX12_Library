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

	//�f�B�X�N���v�^�q�[�v�̐���
	auto result = pDevice->CreateDescriptorHeap(
		/*pDescriptorHeapDesc*/ &desc,
		/*ppDescriptorHeap   */ IID_PPV_ARGS(mDescHeap.ReleaseAndGetAddressOf())
	);

	if (FAILED(result))
	{
#ifdef _DEBUG
		std::cout << "�f�B�X�N���v�^�q�[�v(CBV_SRV_UAV)�̐����Ɏ��s" << std::endl;
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

	//�f�B�X�N���v�^�q�[�v�̐���
	auto result = pDevice->CreateDescriptorHeap(
		/*pDescriptorHeapDesc*/ &desc,
		/*ppDescriptorHeap   */ IID_PPV_ARGS(mDescHeap.ReleaseAndGetAddressOf())
	);

	if (FAILED(result))
	{
#ifdef _DEBUG
		std::cout << "�f�B�X�N���v�^�q�[�v(RTV)�̐����Ɏ��s" << std::endl;
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

	//�f�B�X�N���v�^�q�[�v�̐���
	auto result = pDevice->CreateDescriptorHeap(
		/*pDescriptorHeapDesc*/ &desc,
		/*ppDescriptorHeap   */ IID_PPV_ARGS(mDescHeap.ReleaseAndGetAddressOf())
	);

	if (FAILED(result))
	{
#ifdef _DEBUG
		std::cout << "�f�B�X�N���v�^�q�[�v(DSV)�̐����Ɏ��s" << std::endl;
#endif
	}
}

HDL_DescriptorHeap::~HDL_DescriptorHeap()
{
	mDescHeap.Reset();
}