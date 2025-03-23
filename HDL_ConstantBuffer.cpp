#include "HDL_ConstantBuffer.h"
#include "HDL_Renderer.h"

HDL_ConstantBuffer::HDL_ConstantBuffer(UINT64 bufferSize)
	: pDevice(HDL_Renderer::GetInstance()->GetDevice())
{
	//リソース生成
	auto heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	auto resDesc  = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);
	auto result   = pDevice->CreateCommittedResource(
		/*HEAP_PROPERTIES*/ &heapProp,
		/*HEAP_FLAG		 */ D3D12_HEAP_FLAG_NONE,
		/*RESOURCE_DESC  */ &resDesc,
		/*RESOURCE_STATE */ D3D12_RESOURCE_STATE_GENERIC_READ,
		/*CLEAR_VALUE	 */ nullptr,
		/*ppResource	 */ IID_PPV_ARGS(mConstantBuff.ReleaseAndGetAddressOf())
	);

	assert(SUCCEEDED(result));

	//コンスタントバッファービューの設定
	mCBV.BufferLocation = mConstantBuff->GetGPUVirtualAddress();
	mCBV.SizeInBytes	= static_cast<UINT>(bufferSize); //全バイト
}

void HDL_ConstantBuffer::CreateCBV(D3D12_CPU_DESCRIPTOR_HANDLE handle)
{
	//コンスタントバッファービューを作成
	pDevice->CreateConstantBufferView(&mCBV, handle);
}

void HDL_ConstantBuffer::CopyBufferToVRAM(void* pSomeThing)
{
	auto result = mConstantBuff->Map(0, nullptr, (void**)&pMappedSomeThing);

	assert(SUCCEEDED(result));
	
	memcpy(pMappedSomeThing, pSomeThing, mCBV.SizeInBytes);
}

void HDL_ConstantBuffer::UpdateCBuffer(void* pSomeThing)
{
	memcpy(pMappedSomeThing, pSomeThing, mCBV.SizeInBytes);
}

HDL_ConstantBuffer::~HDL_ConstantBuffer()
{
	mConstantBuff.Reset();
}