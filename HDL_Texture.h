#pragma once
#include "CommonDX12Header.h"
#include <string>

//DirectXTex
#include "/Add-Ons/DirectXTex-main/DirectXTex/DirectXTex.h"

using namespace DirectX;

/// <summary>
/// �e�N�X�`���f�[�^������
/// </summary>
class HDL_Texture
{
public:
	HDL_Texture(const wchar_t* filePath);

	/// <summary>
	/// TexMetaData��Ԃ�
	/// </summary>
	TexMetadata&  GetMetaData() { return mMetaData; }

	/// <summary>
	/// Image��Ԃ�
	/// </summary>
	/// <returns></returns>
	const Image GetImage() const { return *pImg; }
	
private:
	TexMetadata  mMetaData	 = {};
	ScratchImage mScratchImg = {};

	const Image* pImg = nullptr;
};

class HDL_TextureBuffer
{
public:
	/// <summary>
	/// TextureBuffer�𐶐� GPU���Ƀf�[�^��]�����Ă���e�N�X�`���f�[�^��ǂݎ��i�����������@�j
	/// </summary>
	/// <param name="metaData">		�e�N�X�`���̃��^�f�[�^		</param>
	/// <param name="pImg">			�C���[�W�f�[�^�̃|�C���^	</param>
	/// <param name="handle">		SRV�p�̃n���h��				</param>
	HDL_TextureBuffer(TexMetadata metaData, const Image& pImg);

	void CreateSRV(D3D12_CPU_DESCRIPTOR_HANDLE handle);

	/// <summary>
	/// �摜�f�[�^��VRAM�փR�s�[����
	/// </summary>
	/// <param name="pImg">	Image�^�̃|�C���^(�]���f�[�^)		</param>
	void CopyBufferToVRAM(const Image& pImg);

	/// <summary>
	/// �e�N�X�`���o�b�t�@��]�����A�R�s�[�悩��V�F�[�_�[���\�[�X�ɐ؂�ւ�
	/// </summary>
	void OpenTextureBuffer();

	/// <summary>
	/// �R�s�[��ɏ�Ԃ�߂�
	/// </summary>
	void CloseTextureBuffer();

	~HDL_TextureBuffer();

private:
	D3D12_TEXTURE_COPY_LOCATION		mSrc = {};
	D3D12_TEXTURE_COPY_LOCATION		mDst = {};
	D3D12_SHADER_RESOURCE_VIEW_DESC mSRV = {};

	class HDL_Renderer*	   pRenderer = nullptr;
	ID3D12Device*		   pDev		 = nullptr;
	ComPtr<ID3D12Resource> mSrcBuff	 = nullptr;
	ComPtr<ID3D12Resource> mDstBuff	 = nullptr;
};

