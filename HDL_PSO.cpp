#include "HDL_PSO.h"
#include "HDL_Renderer.h"
#include "ShaderCompiler.h"

HDL_PSO::HDL_PSO(D3D12_INPUT_LAYOUT_DESC inputLayout, ID3D12RootSignature* pRootSig)
	: pDevice(HDL_Renderer::GetInstance()->GetDevice())
{
	//PipelineState‚ÌÝ’è
	pipelineDesc.SampleMask						  =	D3D12_DEFAULT_SAMPLE_MASK;
	pipelineDesc.RasterizerState				  =	CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	pipelineDesc.RasterizerState.CullMode		  =	D3D12_CULL_MODE_BACK;
	pipelineDesc.IBStripCutValue				  =	D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
	pipelineDesc.PrimitiveTopologyType			  =	D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	pipelineDesc.NumRenderTargets				  =	1;
	pipelineDesc.RTVFormats[0]				 	  =	DXGI_FORMAT_R8G8B8A8_UNORM;
	pipelineDesc.DSVFormat					  	  =	DXGI_FORMAT_D32_FLOAT;
	pipelineDesc.SampleDesc.Count				  =	1;
	pipelineDesc.SampleDesc.Quality				  =	0;
	pipelineDesc.BlendState						  =	CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	pipelineDesc.DepthStencilState.DepthEnable    = true;
	pipelineDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	pipelineDesc.DepthStencilState.DepthFunc	  =	D3D12_COMPARISON_FUNC_LESS;	
	pipelineDesc.InputLayout					  =	inputLayout;
	pipelineDesc.pRootSignature					  =	pRootSig;
}

void HDL_PSO::SetVS(const LPCWSTR& filePath, LPCSTR version, LPCSTR entryPoint)
{
	auto vs = CompileShader(filePath, version, entryPoint);
	pipelineDesc.VS.BytecodeLength  = vs->GetBufferSize();
	pipelineDesc.VS.pShaderBytecode = vs->GetBufferPointer();
}

void HDL_PSO::SetPS(const LPCWSTR& filePath, LPCSTR version, LPCSTR entryPoint)
{
	auto ps = CompileShader(filePath, version, entryPoint);
	pipelineDesc.PS.BytecodeLength  = ps->GetBufferSize();
	pipelineDesc.PS.pShaderBytecode = ps->GetBufferPointer();
}

void HDL_PSO::CreatePipeline()
{
	auto result = pDevice->CreateGraphicsPipelineState(
		/*D3D12_GRAPHICS_PIPELINE_STATE_DESC*/ &pipelineDesc,
		/*ppPipelineState					*/ IID_PPV_ARGS(mPipeline.ReleaseAndGetAddressOf())
	);

	assert(SUCCEEDED(result));
}

HDL_PSO::~HDL_PSO()
{
	mPipeline.Reset();
}
