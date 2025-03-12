#pragma once
#include "CommonDX12Header.h"

class HDL_DescriptorHeap
{
public:
	/// <summary>
	/// HDL_DescriptorHeapクラスを初期化
	/// </summary>
	HDL_DescriptorHeap();

	/// <summary>
	/// HDL_DescriptorHeapをCBV, SRV, UAVのどれかで作成
	/// </summary>
	/// <param name="numDescriptors">	View(Descriptor)の数	</param>
	void CreateAsCBV_SRV_UAV(UINT numDescriptors);

	/// <summary>
	/// HDL_DescriptorHeapをRTVで作成
	/// </summary>
	/// <param name="numDescriptors">	View(Descriptor)の数	</param>
	void CreateAsRTV(UINT numDescriptors);

	/// <summary>
	/// HDL_DescriptorHeapをDSVで作成
	/// </summary>
	/// <param name="numDescriptors">	View(Descriptor)の数	</param>
	void CreateAsDSV(UINT numDescriptors);

	~HDL_DescriptorHeap();

	/// <summary>
	/// DescriptorHeapのポインターを返す
	/// </summary>
	/// <returns>	ComPtr.Get()	</returns>
	ID3D12DescriptorHeap* GetPointerOfDescriptorHeap() const { return mDescHeap.Get(); }

	/// <summary>
	/// DescriptorHeapのアドレスを返す
	/// </summary>
	/// <returns>	ComPtr.GetAddressOf()	</returns>
	ID3D12DescriptorHeap** GetAddressOfDescriptorHeap() { return mDescHeap.GetAddressOf(); }

private:
	ID3D12Device*				 pDevice   = nullptr;
	ComPtr<ID3D12DescriptorHeap> mDescHeap = nullptr;
};

