#pragma once
#include "CommonDX12Header.h"

class HDL_DescriptorHeap
{
public:
	/// <summary>
	/// HDL_DescriptorHeap�N���X��������
	/// </summary>
	HDL_DescriptorHeap();

	/// <summary>
	/// HDL_DescriptorHeap��CBV, SRV, UAV�̂ǂꂩ�ō쐬
	/// </summary>
	/// <param name="numDescriptors">	View(Descriptor)�̐�	</param>
	void CreateAsCBV_SRV_UAV(UINT numDescriptors);

	/// <summary>
	/// HDL_DescriptorHeap��RTV�ō쐬
	/// </summary>
	/// <param name="numDescriptors">	View(Descriptor)�̐�	</param>
	void CreateAsRTV(UINT numDescriptors);

	/// <summary>
	/// HDL_DescriptorHeap��DSV�ō쐬
	/// </summary>
	/// <param name="numDescriptors">	View(Descriptor)�̐�	</param>
	void CreateAsDSV(UINT numDescriptors);

	~HDL_DescriptorHeap();

	/// <summary>
	/// DescriptorHeap�̒��g��Ԃ�
	/// </summary>
	/// <returns>	ComPtr.Get()	</returns>
	ID3D12DescriptorHeap* GetPointerOfDescriptorHeap() const { return mDescHeap.Get(); }

	/// <summary>
	/// DescriptorHeap�̃|�C���^�̃A�h���X��Ԃ�
	/// </summary>
	/// <returns>	ComPtr.GetAddressOf()	</returns>
	ID3D12DescriptorHeap** GetAddressOfDescriptorHeap() { return mDescHeap.GetAddressOf(); }

	/// <summary>
	/// CPU���HeapHandle�J�n�����擾
	/// </summary>
	D3D12_CPU_DESCRIPTOR_HANDLE GetHeapStart_In_CPU() const { return mHeapHandle_CPU; }

	/// <summary>
	/// GPU���HeapHandle�J�n�����擾
	/// </summary>
	D3D12_GPU_DESCRIPTOR_HANDLE GetHeapStart_In_GPU() const { return mHeapHandle_GPU; }

private:
	ID3D12Device*				 pDevice   = nullptr;
	ComPtr<ID3D12DescriptorHeap> mDescHeap = nullptr;
	D3D12_CPU_DESCRIPTOR_HANDLE  mHeapHandle_CPU = {};
	D3D12_GPU_DESCRIPTOR_HANDLE  mHeapHandle_GPU = {};

	void GetHandle();
};

