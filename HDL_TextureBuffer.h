#pragma once
#include "CommonDX12Header.h"

//DirectXTex
#include "/Add-Ons/DirectXTex-main/DirectXTex/DirectXTex.h"

using namespace DirectX;


class HDL_TextureBuffer
{
public:
	/// <summary>
	/// TextureBufferを生成 GPU側にデータを転送してからテクスチャデータを読み取る（公式推奨方法）
	/// </summary>
	/// <param name="metaData">		テクスチャのメタデータ		</param>
	/// <param name="pImg">			イメージデータのポインタ	</param>
	/// <param name="handle">		SRV用のハンドル				</param>
	HDL_TextureBuffer(TexMetadata metaData, const Image* pImg, D3D12_CPU_DESCRIPTOR_HANDLE handle);

	/// <summary>
	/// 画像データをVRAMへコピーする
	/// </summary>
	/// <param name="pImg">	Image型のポインタ(転送データ)		</param>
	void CopyBufferToVRAM(const Image* pImg);

	/// <summary>
	/// テクスチャバッファを転送し、コピー先からシェーダーリソースに切り替え
	/// </summary>
	void OpenTextureBuffer();

	/// <summary>
	/// コピー先に状態を戻す
	/// </summary>
	void CloseTextureBuffer();

	~HDL_TextureBuffer();

private:
	D3D12_TEXTURE_COPY_LOCATION		mSrc = {};
	D3D12_TEXTURE_COPY_LOCATION		mDst = {};
	D3D12_SHADER_RESOURCE_VIEW_DESC mSRV = {};

	class HDL_Renderer*	   pRenderer = nullptr;
	ComPtr<ID3D12Resource> mSrcBuff	 = nullptr;
	ComPtr<ID3D12Resource> mDstBuff	 = nullptr;
};

