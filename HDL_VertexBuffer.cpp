#include "HDL_VertexBuffer.h"
#include "HDL_Renderer.h"

HDL_VertexBuffer::HDL_VertexBuffer(UINT64 bufferSize, UINT stride) :
	pDevice(HDL_Renderer::GetInstance()->GetDevice())
{
	//���\�[�X����
	auto heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	auto resDesc  = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);
	auto result	  = pDevice->CreateCommittedResource(
		/*HEAP_PROPERTIES*/ &heapProp,
		/*HEAP_FLAG		 */ D3D12_HEAP_FLAG_NONE,
		/*RESOURCE_DESC  */ &resDesc,
		/*RESOURCE_STATE */ D3D12_RESOURCE_STATE_GENERIC_READ,
		/*CLEAR_VALUE	 */ nullptr,
		/*ppResource	 */ IID_PPV_ARGS(mVertexBuff.ReleaseAndGetAddressOf())
	);

	assert(SUCCEEDED(result));

	//�o�[�e�b�N�X�o�b�t�@�r���[�̐ݒ�
	mVBV.BufferLocation = mVertexBuff->GetGPUVirtualAddress();
	mVBV.SizeInBytes	= static_cast<UINT>(bufferSize);   //�S�o�C�g
	mVBV.StrideInBytes	= static_cast<UINT>(stride);	   //���_�������̃T�C�Y
}

void HDL_VertexBuffer::CopyBufferToVRAM(void* pVertices)
{
	void* mappedVertices = nullptr;
	auto  result		 = mVertexBuff->Map(0, nullptr, (void**)&mappedVertices);

	assert(SUCCEEDED(result));

	memcpy(mappedVertices, pVertices, mVBV.SizeInBytes);
	mVertexBuff->Unmap(0, nullptr);
}

HDL_VertexBuffer::~HDL_VertexBuffer()
{
	mVertexBuff.Reset();
}