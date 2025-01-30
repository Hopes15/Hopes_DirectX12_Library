#include "HDL_TextureBuffer.h"
#include "HDL_Renderer.h"
#include "Utilities.h"

HDL_TextureBuffer::HDL_TextureBuffer(TexMetadata metaData, const Image* pImg, D3D12_CPU_DESCRIPTOR_HANDLE handle) :
	pRenderer(HDL_Renderer::GetInstance())
{
	auto dev = pRenderer->GetDevice();

	//バッファサイズをアライン
	auto bufferSize = AlignBufferSize(pImg->rowPitch, D3D12_TEXTURE_DATA_PITCH_ALIGNMENT) * pImg->height;

	//コピー元リソースの生成
	auto heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	auto resDesc  = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);
	auto result   = dev->CreateCommittedResource(
		/*HEAP_PROPERTIES*/ &heapProp,
		/*HEAP_FLAG		 */ D3D12_HEAP_FLAG_NONE,
		/*RESOURCE_DESC  */ &resDesc,
		/*RESOURCE_STATE */ D3D12_RESOURCE_STATE_GENERIC_READ,
		/*CLEAR_VALUE	 */ nullptr,
		/*ppResource	 */ IID_PPV_ARGS(mSrcBuff.ReleaseAndGetAddressOf())
	);

	if (FAILED(result)) 
	{
#ifdef _DEBUG
		std::cout << "コピー元リソースの生成に失敗" << std::endl;
#endif
	}

	//コピー先リソースの作成
	heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	resDesc  = CD3DX12_RESOURCE_DESC(
		/*Resource Dimension*/ static_cast<D3D12_RESOURCE_DIMENSION>(metaData.dimension),
		/*Alignment			*/ 0,
		/*Width				*/ metaData.width,
		/*Height			*/ static_cast<UINT  >(metaData.height),
		/*DepthOrArraySize	*/ static_cast<UINT16>(metaData.arraySize),
		/*MipLevels			*/ static_cast<UINT16>(metaData.mipLevels),
		/*Format			*/ metaData.format,
		/*SampleCount		*/ 1,
		/*SampleQuality		*/ 0,
		/*Texture Layout	*/ D3D12_TEXTURE_LAYOUT_UNKNOWN,
		/*Resource Flags	*/ D3D12_RESOURCE_FLAG_NONE
	);
	result	 = dev->CreateCommittedResource(
		/*HEAP_PROPERTIES*/ &heapProp,
		/*HEAP_FLAG		 */ D3D12_HEAP_FLAG_NONE,
		/*RESOURCE_DESC  */ &resDesc,
		/*RESOURCE_STATE */ D3D12_RESOURCE_STATE_COPY_DEST,
		/*CLEAR_VALUE	 */ nullptr,
		/*ppResource	 */ IID_PPV_ARGS(mDstBuff.ReleaseAndGetAddressOf())
	);

	if (FAILED(result)) 
	{
#ifdef _DEBUG
		std::cout << "コピー先リソースの生成に失敗" << std::endl;
#endif
	}

	//SRVの作成
	mSRV.Format					 = metaData.format;
	mSRV.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	mSRV.ViewDimension			 = D3D12_SRV_DIMENSION_TEXTURE2D;
	mSRV.Texture2D.MipLevels	 = 1;

	dev->CreateShaderResourceView(
		/*pResource */ mDstBuff.Get(),
		/*pSRV	    */ &mSRV,
		/*heaphandle*/ handle
	);

	//コピー元の設定
	mSrc.pResource							= mSrcBuff.Get();
	mSrc.Type								= D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
	mSrc.PlacedFootprint.Offset				= 0;
	mSrc.PlacedFootprint.Footprint.Width	= static_cast<UINT>(metaData.width);
	mSrc.PlacedFootprint.Footprint.Height	= static_cast<UINT>(metaData.height);
	mSrc.PlacedFootprint.Footprint.Depth	= static_cast<UINT>(metaData.depth);
	mSrc.PlacedFootprint.Footprint.RowPitch = static_cast<UINT>(AlignBufferSize(pImg->rowPitch, D3D12_TEXTURE_DATA_PITCH_ALIGNMENT));
	mSrc.PlacedFootprint.Footprint.Format	= pImg->format;

	//コピー先の設定
	mDst.pResource		  = mDstBuff.Get();
	mDst.Type			  = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
	mDst.SubresourceIndex = 0;
}

void HDL_TextureBuffer::CopyBufferToVRAM(const Image* pImg)
{
	uint8_t* pMappedTex = nullptr;
	auto result			= mSrcBuff->Map(0, nullptr, (void**)&pMappedTex);

	if (FAILED(result))
	{
#ifdef _DEBUG
		std::cout << "UploadBufferのマッピングに失敗" << std::endl;
#endif
	}

	//コピー
	auto srcAddress = pImg->pixels;
	auto rowPitch	= AlignBufferSize(pImg->rowPitch, D3D12_TEXTURE_DATA_PITCH_ALIGNMENT);

	//つじつま合わせ
	for (size_t h = 0; h < pImg->height; ++h)
	{
		std::copy_n(srcAddress, rowPitch, pMappedTex);

		srcAddress += pImg->rowPitch;
		pMappedTex += rowPitch;
	}

	mSrcBuff->Unmap(0, nullptr);
}

void HDL_TextureBuffer::OpenTextureBuffer()
{
	auto cmdList = pRenderer->GetCmdList();

	//テクスチャデータをコピー元からコピー先へ転送
	cmdList->CopyTextureRegion(&mDst, 0, 0, 0, &mSrc, nullptr);

	//リソースバリア
	auto transition = CD3DX12_RESOURCE_BARRIER::Transition(
		/*pResouce*/ mDstBuff.Get(),
		/*Before  */ D3D12_RESOURCE_STATE_COPY_DEST,
		/*After   */ D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE
	);
	cmdList->ResourceBarrier(1, &transition);
}

void HDL_TextureBuffer::CloseTextureBuffer()
{
	auto cmdList	 = pRenderer->GetCmdList();

	//リソースバリア
	auto transition = CD3DX12_RESOURCE_BARRIER::Transition(
		/*pResouce*/ mDstBuff.Get(),
		/*Before  */ D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		/*After   */ D3D12_RESOURCE_STATE_COPY_DEST
	);
	cmdList->ResourceBarrier(1, &transition);
}

HDL_TextureBuffer::~HDL_TextureBuffer()
{
	mDstBuff.Reset();
	mSrcBuff.Reset();
}