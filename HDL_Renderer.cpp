#include "HDL_Renderer.h"

HDL_Renderer* HDL_Renderer::pInstance = nullptr;

HDL_Renderer::HDL_Renderer(UINT WIDTH, UINT HEIGHT, HWND hwnd) :
	WINDOW_WIDTH (WIDTH),
	WINDOW_HEIGHT(HEIGHT),
	mHWND		 (hwnd),
	BUFFER_COUNT (2),
	mFenceVal	 (0)
{
#ifdef _DEBUG
	EnableDebugLayer();
#endif

	//���W���[���̏�����
	if (!CreateFactory())	   return;
	if (!CreateDevice())	   return;
	if (!CreateCmdAllocator()) return;
	if (!CreateCmdList())	   return;
	if (!CreateCmdQueue())	   return;
	if (!CreateSwapChain())	   return;
	if (!CreateFence())		   return;
}

HDL_Renderer::~HDL_Renderer()
{
	WaitDrawing();

	//���
	mFence.Reset();
	mSwapChain4.Reset();
	mCmdQueue.Reset();
	mCmdList.Reset();
	mCmdAllocator.Reset();
	mDevice.Reset();
	mAdapter.Reset();
}

void HDL_Renderer::EnterDrawing()
{
	//���߂̃��Z�b�g
	mCmdAllocator->Reset();
	mCmdList->Reset(mCmdAllocator.Get(), nullptr);
}

void HDL_Renderer::SetRenderTargets(D3D12_CPU_DESCRIPTOR_HANDLE* pRTDesc, D3D12_CPU_DESCRIPTOR_HANDLE* pDSDesc)
{
	mCmdList->OMSetRenderTargets(1, pRTDesc, false, pDSDesc);
}

void HDL_Renderer::ExitDrawing()
{
	//���߂̃N���[�Y
	mCmdList->Close();

	//���߂����s
	ID3D12CommandList* cmdLists[] = { mCmdList.Get() };
	mCmdQueue->ExecuteCommandLists(_countof(cmdLists), cmdLists);

	//�`�抮���܂ő҂�
	WaitDrawing();

	//��ʃt���b�v
	mSwapChain4->Present(1, 0);
}

//Create�֐�
bool HDL_Renderer::CreateFactory()
{
	//Factory�̐���
#ifdef _DEBUG
	auto result = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(mFactory.ReleaseAndGetAddressOf()));
#else
	auto result = CreateDXGIFactory1(IID_PPV_ARGS(mFactory.ReleaseAndGetAddressOf()));
#endif

	assert(SUCCEEDED(result));

	//�A�_�v�^�[�̗�
	std::vector<ComPtr<IDXGIAdapter>> adapters;

	for (int i = 0; mFactory->EnumAdapters(i, mAdapter.ReleaseAndGetAddressOf()) != DXGI_ERROR_NOT_FOUND; ++i)
	{
		adapters.push_back(mAdapter.Get());
	}

	for (auto& adpt : adapters)
	{
		DXGI_ADAPTER_DESC desc = {};
		adpt->GetDesc(&desc);

		std::wstring strDesc = desc.Description;

		//TODO:�ʃf�o�C�X�ɂ��Ή�����悤�ɂ���
		//NVIDIA
		if (strDesc.find(L"NVIDIA") != std::string::npos)
		{
			mAdapter = adpt;
			break;
		}
	}

	//�s�v�ɂȂ����̂ŉ��
	for (auto& adpt : adapters) adpt.Reset();

	return true;
}

bool HDL_Renderer::CreateDevice()
{
	//�t�B�[�`���[���x���̗�
	D3D_FEATURE_LEVEL levels[] =
	{
		D3D_FEATURE_LEVEL_12_2,
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};

	//���p�\�ȃt�B�[�`���[���x����I��
	D3D_FEATURE_LEVEL  featureLevel;
	for (auto lv : levels)
	{
		if (D3D12CreateDevice(mAdapter.Get(), lv, IID_PPV_ARGS(mDevice.ReleaseAndGetAddressOf())) == S_OK)
		{
			featureLevel = lv;
			break;
		}
	}

	//�f�o�C�X�쐬
	auto result = D3D12CreateDevice(mAdapter.Get(), featureLevel, IID_PPV_ARGS(mDevice.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));

	return true;
}

bool HDL_Renderer::CreateCmdAllocator()
{
	//�R�}���h�A���P�[�^�[�̐���
	auto result = mDevice->CreateCommandAllocator(
		/*COMMAND_LIST_TYPE */ D3D12_COMMAND_LIST_TYPE_DIRECT,
		/*ppCommandAllocator*/ IID_PPV_ARGS(mCmdAllocator.ReleaseAndGetAddressOf())
	);

	assert(SUCCEEDED(result));

	return true;
}

bool HDL_Renderer::CreateCmdList()
{
	//�R�}���h���X�g�̐���
	auto result = mDevice->CreateCommandList(
		/*nodeMask         */ 0,
		/*COMMAND_LIST_TYPE*/ D3D12_COMMAND_LIST_TYPE_DIRECT,
		/*pCommandAllocator*/ mCmdAllocator.Get(),
		/*pInitialState    */ nullptr,
		/*ppCommandList    */ IID_PPV_ARGS(mCmdList.ReleaseAndGetAddressOf())
	);

	assert(SUCCEEDED(result));

	//���߂��N���[�Y���Ď󂯕t���鏀��
	mCmdList->Close();

	return true;
}

bool HDL_Renderer::CreateCmdQueue()
{
	//�R�}���h�L���[�̐ݒ�
	D3D12_COMMAND_QUEUE_DESC desc = {};
	desc.Flags		= D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.NodeMask	= 0;
	desc.Priority	= D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	desc.Type		= D3D12_COMMAND_LIST_TYPE_DIRECT;

	//�R�}���h�L���[�𐶐�
	auto result = mDevice->CreateCommandQueue(
		/*COMMAND_QUEUE_DESC*/ &desc,
		/*ppCommandQueue    */ IID_PPV_ARGS(mCmdQueue.ReleaseAndGetAddressOf())
	);

	assert(SUCCEEDED(result));

	return true;
}

bool HDL_Renderer::CreateSwapChain()
{
	//�X���b�v�`�F�[���̐ݒ�
	DXGI_SWAP_CHAIN_DESC1 desc = {};
	desc.Width				= WINDOW_WIDTH;
	desc.Height				= WINDOW_HEIGHT;
	desc.Format				= DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.Stereo				= false;
	desc.SampleDesc.Count	= 1;
	desc.SampleDesc.Quality = 0;
	desc.BufferUsage		= DXGI_USAGE_BACK_BUFFER;
	desc.BufferCount		= BUFFER_COUNT;
	desc.Scaling			= DXGI_SCALING_STRETCH;
	desc.SwapEffect			= DXGI_SWAP_EFFECT_FLIP_DISCARD;
	desc.AlphaMode			= DXGI_ALPHA_MODE_UNSPECIFIED;
	desc.Flags				= DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	//�X���b�v�`�F�[���̐���
	ComPtr<IDXGISwapChain1> swapChain1 = nullptr;
	auto result = mFactory->CreateSwapChainForHwnd(
		/*pCommandQueue	   */ mCmdQueue.Get(),
		/*HWND			   */ mHWND,
		/*SWAP_CHAIN_DESC1 */ &desc,
		/*pFullScreenDesc  */ nullptr,
		/*pRestrictToOutput*/ nullptr,
		/*ppSwapChain	   */ swapChain1.ReleaseAndGetAddressOf()
	);

	assert(SUCCEEDED(result));

	//SwapChain4�ւ̌݊��������邩���m�F
	result = swapChain1->QueryInterface(IID_PPV_ARGS(mSwapChain4.ReleaseAndGetAddressOf()));

	assert(SUCCEEDED(result));

	//���
	swapChain1.Reset();
	mFactory.Reset();

	return true;
}

bool HDL_Renderer::CreateFence()
{
	//�t�F���X�𐶐�
	auto result = mDevice->CreateFence(
		/*InitialFenceValue*/ mFenceVal,
		/*FENCE_FLAG	   */ D3D12_FENCE_FLAG_NONE,
		/*ppFence          */ IID_PPV_ARGS(mFence.ReleaseAndGetAddressOf())
	);

	assert(SUCCEEDED(result));

	return true;
}

//Draw�֘A
void HDL_Renderer::WaitDrawing()
{
	//�t�F���X����
	mCmdQueue->Signal(mFence.Get(), ++mFenceVal);

	if (mFence->GetCompletedValue() != mFenceVal)
	{
		//�C�x���g�n���h���̎擾
		auto event = CreateEvent(nullptr, false, false, nullptr);
		//�C�x���g�̃Z�b�g
		mFence->SetEventOnCompletion(mFenceVal, event);
		//�C�x���g����������܂ő҂�
		WaitForSingleObject(event, INFINITE);
		//�C�x���g�n���h�������
		CloseHandle(event);
	}
}

//���̑�
void HDL_Renderer::EnableDebugLayer() 
{
	ComPtr<ID3D12Debug>	debugLayer = nullptr;
	auto result = D3D12GetDebugInterface(IID_PPV_ARGS(debugLayer.ReleaseAndGetAddressOf()));

	if (FAILED(result))
	{
		std::cout << "�f�o�b�N���C���[�̐����Ɏ��s" << std::endl;
		return;
	}

	debugLayer->EnableDebugLayer();
	debugLayer.Reset();
}