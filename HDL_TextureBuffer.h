#pragma once
#include "CommonDX12Header.h"

//DirectXTex
#include "/Add-Ons/DirectXTex-main/DirectXTex/DirectXTex.h"

using namespace DirectX;


class HDL_TextureBuffer
{
public:
	/// <summary>
	/// TextureBuffer�𐶐� GPU���Ƀf�[�^��]�����Ă���e�N�X�`���f�[�^��ǂݎ��i�����������@�j
	/// </summary>
	/// <param name="metaData">		�e�N�X�`���̃��^�f�[�^		</param>
	/// <param name="pImg">			�C���[�W�f�[�^�̃|�C���^	</param>
	/// <param name="handle">		SRV�p�̃n���h��				</param>
	HDL_TextureBuffer(TexMetadata metaData, const Image* pImg, D3D12_CPU_DESCRIPTOR_HANDLE handle);

	/// <summary>
	/// �摜�f�[�^��VRAM�փR�s�[����
	/// </summary>
	/// <param name="pImg">	Image�^�̃|�C���^(�]���f�[�^)		</param>
	void CopyBufferToVRAM(const Image* pImg);

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
	ComPtr<ID3D12Resource> mSrcBuff	 = nullptr;
	ComPtr<ID3D12Resource> mDstBuff	 = nullptr;
};

