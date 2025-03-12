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
	/// DescriptorHeap�̃|�C���^�[��Ԃ�
	/// </summary>
	/// <returns>	ComPtr.Get()	</returns>
	ID3D12DescriptorHeap* GetPointerOfDescriptorHeap() const { return mDescHeap.Get(); }

	/// <summary>
	/// DescriptorHeap�̃A�h���X��Ԃ�
	/// </summary>
	/// <returns>	ComPtr.GetAddressOf()	</returns>
	ID3D12DescriptorHeap** GetAddressOfDescriptorHeap() { return mDescHeap.GetAddressOf(); }

private:
	ID3D12Device*				 pDevice   = nullptr;
	ComPtr<ID3D12DescriptorHeap> mDescHeap = nullptr;
};

