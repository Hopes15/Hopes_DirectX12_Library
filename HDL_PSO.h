#pragma once
#include "CommonDX12Header.h"

class HDL_PSO
{
	public:
	/// <summary>
	/// HDL_PSOオブジェクトを初期化, パイプラインステートに必要な要素を引数にとる
	/// </summary>
	/// <param name="inputLayout">	セットするインプットレイアウト		</param>
	/// <param name="pRootSig">		セットするRootSignatureのポインタ	</param>
	/// <param name="pVSBlob">		セットするVSBlobのポインタ			</param>
	/// <param name="pPSBlob">		セットするPSBlobのポインタ			</param>
	HDL_PSO(D3D12_INPUT_LAYOUT_DESC inputLayout, ID3D12RootSignature *pRootSig);

	/// <summary>
	/// PSOにVSをコンパイルしてからセットする
	/// </summary>
	/// <param name="filePath">		シェーダーファイルのパス　</param>
	/// <param name="version">		シェーダーバージョン　	　</param>
	/// <param name="entryPoin">	エントリーポイント		　</param>
	void SetVS(const LPCWSTR& filePath, LPCSTR version = "vs_5_0", LPCSTR entryPoint = "main");

	/// <summary>
	/// PSOにPSをコンパイルしてからセットする
	/// </summary>
	/// <param name="filePath">		シェーダーファイルのパス　</param>
	/// <param name="version">		シェーダーバージョン　	　</param>
	/// <param name="entryPoin">	エントリーポイント		　</param>
	void SetPS(const LPCWSTR& filePath, LPCSTR version = "ps_5_0", LPCSTR entryPoint = "main");

	/// <summary>
	/// ID3D12PipelineStateオブジェクトを作成する
	/// </summary>
	void CreatePipeline();

	/// <summary>
	/// ID3D12PipelineStateのポインタを返す
	/// </summary>
	/// <returns>	ComPtr.Get()	</returns>
	ID3D12PipelineState* GetPointerOfPipeline() { return mPipeline.Get(); }

	~HDL_PSO();

private:
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc = {};

	ComPtr<ID3D12PipelineState> mPipeline = nullptr;
	ID3D12Device*				pDevice   = nullptr;
};

