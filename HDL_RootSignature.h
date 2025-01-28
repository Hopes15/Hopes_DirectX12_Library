#pragma once
#include "CommonDX12Header.h"

class HDL_RootSignature
{
public:
	/// <summary>
	/// HDL_RootSignature�N���X��������
	/// </summary>
	/// <param name="pRootSigDesc">	RootSignatureDesc�̃|�C���^	</param>
	HDL_RootSignature(D3D12_ROOT_SIGNATURE_DESC* pRootSigDesc);

	/// <summary>
	/// ID3D12RootSignature�I�u�W�F�N�g���쐬����
	/// </summary>
	void CreateRootSignature();

	/// <summary>
	/// ID3D12RootSignature�̃|�C���^�[��Ԃ�
	/// </summary>
	/// <returns>	ComPtr.Get()	</returns>
	ID3D12RootSignature* GetPointerOfRootSignature() { return mRootSig.Get(); }

	~HDL_RootSignature();

private:
	ID3D12Device* pDevice					= nullptr;
	ComPtr<ID3D12RootSignature> mRootSig	= nullptr;
	ComPtr<ID3DBlob>		    rootSigBlob = nullptr;
};

