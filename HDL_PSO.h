#pragma once
#include "CommonDX12Header.h"

class HDL_PSO
{
	public:
	/// <summary>
	/// HDL_PSO�I�u�W�F�N�g��������, �p�C�v���C���X�e�[�g�ɕK�v�ȗv�f�������ɂƂ�
	/// </summary>
	/// <param name="inputLayout">	�Z�b�g����C���v�b�g���C�A�E�g		</param>
	/// <param name="pRootSig">		�Z�b�g����RootSignature�̃|�C���^	</param>
	/// <param name="pVSBlob">		�Z�b�g����VSBlob�̃|�C���^			</param>
	/// <param name="pPSBlob">		�Z�b�g����PSBlob�̃|�C���^			</param>
	HDL_PSO(D3D12_INPUT_LAYOUT_DESC inputLayout, ID3D12RootSignature *pRootSig);

	/// <summary>
	/// PSO��VS���R���p�C�����Ă���Z�b�g����
	/// </summary>
	/// <param name="filePath">		�V�F�[�_�[�t�@�C���̃p�X�@</param>
	/// <param name="version">		�V�F�[�_�[�o�[�W�����@	�@</param>
	/// <param name="entryPoin">	�G���g���[�|�C���g		�@</param>
	void SetVS(const LPCWSTR& filePath, LPCSTR version = "vs_5_0", LPCSTR entryPoint = "main");

	/// <summary>
	/// PSO��PS���R���p�C�����Ă���Z�b�g����
	/// </summary>
	/// <param name="filePath">		�V�F�[�_�[�t�@�C���̃p�X�@</param>
	/// <param name="version">		�V�F�[�_�[�o�[�W�����@	�@</param>
	/// <param name="entryPoin">	�G���g���[�|�C���g		�@</param>
	void SetPS(const LPCWSTR& filePath, LPCSTR version = "ps_5_0", LPCSTR entryPoint = "main");

	/// <summary>
	/// ID3D12PipelineState�I�u�W�F�N�g���쐬����
	/// </summary>
	void CreatePipeline();

	/// <summary>
	/// ID3D12PipelineState�̃|�C���^��Ԃ�
	/// </summary>
	/// <returns>	ComPtr.Get()	</returns>
	ID3D12PipelineState* GetPointerOfPipeline() { return mPipeline.Get(); }

	~HDL_PSO();

private:
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc = {};

	ComPtr<ID3D12PipelineState> mPipeline = nullptr;
	ID3D12Device*				pDevice   = nullptr;
};

