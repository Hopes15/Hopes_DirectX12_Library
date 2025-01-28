#pragma once
#include "CommonDX12Header.h"

class HDL_RootSignature
{
public:
	/// <summary>
	/// HDL_RootSignatureクラスを初期化
	/// </summary>
	/// <param name="pRootSigDesc">	RootSignatureDescのポインタ	</param>
	HDL_RootSignature(D3D12_ROOT_SIGNATURE_DESC* pRootSigDesc);

	/// <summary>
	/// ID3D12RootSignatureオブジェクトを作成する
	/// </summary>
	void CreateRootSignature();

	/// <summary>
	/// ID3D12RootSignatureのポインターを返す
	/// </summary>
	/// <returns>	ComPtr.Get()	</returns>
	ID3D12RootSignature* GetPointerOfRootSignature() { return mRootSig.Get(); }

	~HDL_RootSignature();

private:
	ID3D12Device* pDevice					= nullptr;
	ComPtr<ID3D12RootSignature> mRootSig	= nullptr;
	ComPtr<ID3DBlob>		    rootSigBlob = nullptr;
};

