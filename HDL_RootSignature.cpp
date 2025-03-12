#include "HDL_RootSignature.h"
#include "HDL_Renderer.h"

HDL_RootSignature::HDL_RootSignature(D3D12_ROOT_SIGNATURE_DESC* pRootSigDesc) : 
	pDevice(HDL_Renderer::GetInstance()->GetDevice())
{
	ComPtr<ID3DBlob> errBlob = nullptr;

	auto result = D3D12SerializeRootSignature(
		/*D3D12_ROOT_SIGNATURE_DESC	*/ pRootSigDesc,
		/*D3D_ROOT_SIGNATURE_VERSION*/ D3D_ROOT_SIGNATURE_VERSION_1_0,
		/*ppBlob					*/ rootSigBlob.ReleaseAndGetAddressOf(),
		/*ppErrorBlob				*/ errBlob.ReleaseAndGetAddressOf()
	);

	//���[�g�V�O�l�`���̃V���A���C�Y
	assert(SUCCEEDED(result));

	//���
	errBlob.Reset();
}

void HDL_RootSignature::CreateRootSignature()
{
	//���[�g�V�O�l�`���𐶐�
	auto result = pDevice->CreateRootSignature(
		/*nodeMask				*/ 0,
		/*pBlobWithRootSignature*/ rootSigBlob->GetBufferPointer(),
		/*blobLengthInBytes     */ rootSigBlob->GetBufferSize(),
		/*ppRootSignature		*/ IID_PPV_ARGS(mRootSig.ReleaseAndGetAddressOf())
	);

	assert(SUCCEEDED(result));

	//���
	rootSigBlob.Reset();
}

HDL_RootSignature::~HDL_RootSignature()
{
	mRootSig.Reset();
}