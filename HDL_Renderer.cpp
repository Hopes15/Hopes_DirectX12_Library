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

	//モジュールの初期化
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

	//解放
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
	//命令のリセット
	mCmdAllocator->Reset();
	mCmdList->Reset(mCmdAllocator.Get(), nullptr);
}

void HDL_Renderer::SetRenderTargets(D3D12_CPU_DESCRIPTOR_HANDLE* pRTDesc, D3D12_CPU_DESCRIPTOR_HANDLE* pDSDesc)
{
	mCmdList->OMSetRenderTargets(1, pRTDesc, false, pDSDesc);
}

void HDL_Renderer::ExitDrawing()
{
	//命令のクローズ
	mCmdList->Close();

	//命令を実行
	ID3D12CommandList* cmdLists[] = { mCmdList.Get() };
	mCmdQueue->ExecuteCommandLists(_countof(cmdLists), cmdLists);

	//描画完了まで待つ
	WaitDrawing();

	//画面フリップ
	mSwapChain4->Present(1, 0);
}

//Create関数
bool HDL_Renderer::CreateFactory()
{
	//Factoryの生成
#ifdef _DEBUG
	auto result = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(mFactory.ReleaseAndGetAddressOf()));
#else
	auto result = CreateDXGIFactory1(IID_PPV_ARGS(mFactory.ReleaseAndGetAddressOf()));
#endif

	assert(SUCCEEDED(result));

	//アダプターの列挙
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

		//TODO:別デバイスにも対応するようにする
		//NVIDIA
		if (strDesc.find(L"NVIDIA") != std::string::npos)
		{
			mAdapter = adpt;
			break;
		}
	}

	//不要になったので解放
	for (auto& adpt : adapters) adpt.Reset();

	return true;
}

bool HDL_Renderer::CreateDevice()
{
	//フィーチャーレベルの列挙
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

	//利用可能なフィーチャーレベルを選択
	D3D_FEATURE_LEVEL  featureLevel;
	for (auto lv : levels)
	{
		if (D3D12CreateDevice(mAdapter.Get(), lv, IID_PPV_ARGS(mDevice.ReleaseAndGetAddressOf())) == S_OK)
		{
			featureLevel = lv;
			break;
		}
	}

	//デバイス作成
	auto result = D3D12CreateDevice(mAdapter.Get(), featureLevel, IID_PPV_ARGS(mDevice.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));

	return true;
}

bool HDL_Renderer::CreateCmdAllocator()
{
	//コマンドアロケーターの生成
	auto result = mDevice->CreateCommandAllocator(
		/*COMMAND_LIST_TYPE */ D3D12_COMMAND_LIST_TYPE_DIRECT,
		/*ppCommandAllocator*/ IID_PPV_ARGS(mCmdAllocator.ReleaseAndGetAddressOf())
	);

	assert(SUCCEEDED(result));

	return true;
}

bool HDL_Renderer::CreateCmdList()
{
	//コマンドリストの生成
	auto result = mDevice->CreateCommandList(
		/*nodeMask         */ 0,
		/*COMMAND_LIST_TYPE*/ D3D12_COMMAND_LIST_TYPE_DIRECT,
		/*pCommandAllocator*/ mCmdAllocator.Get(),
		/*pInitialState    */ nullptr,
		/*ppCommandList    */ IID_PPV_ARGS(mCmdList.ReleaseAndGetAddressOf())
	);

	assert(SUCCEEDED(result));

	//命令をクローズして受け付ける準備
	mCmdList->Close();

	return true;
}

bool HDL_Renderer::CreateCmdQueue()
{
	//コマンドキューの設定
	D3D12_COMMAND_QUEUE_DESC desc = {};
	desc.Flags		= D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.NodeMask	= 0;
	desc.Priority	= D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	desc.Type		= D3D12_COMMAND_LIST_TYPE_DIRECT;

	//コマンドキューを生成
	auto result = mDevice->CreateCommandQueue(
		/*COMMAND_QUEUE_DESC*/ &desc,
		/*ppCommandQueue    */ IID_PPV_ARGS(mCmdQueue.ReleaseAndGetAddressOf())
	);

	assert(SUCCEEDED(result));

	return true;
}

bool HDL_Renderer::CreateSwapChain()
{
	//スワップチェーンの設定
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

	//スワップチェーンの生成
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

	//SwapChain4への互換性があるかを確認
	result = swapChain1->QueryInterface(IID_PPV_ARGS(mSwapChain4.ReleaseAndGetAddressOf()));

	assert(SUCCEEDED(result));

	//解放
	swapChain1.Reset();
	mFactory.Reset();

	return true;
}

bool HDL_Renderer::CreateFence()
{
	//フェンスを生成
	auto result = mDevice->CreateFence(
		/*InitialFenceValue*/ mFenceVal,
		/*FENCE_FLAG	   */ D3D12_FENCE_FLAG_NONE,
		/*ppFence          */ IID_PPV_ARGS(mFence.ReleaseAndGetAddressOf())
	);

	assert(SUCCEEDED(result));

	return true;
}

//Draw関連
void HDL_Renderer::WaitDrawing()
{
	//フェンス処理
	mCmdQueue->Signal(mFence.Get(), ++mFenceVal);

	if (mFence->GetCompletedValue() != mFenceVal)
	{
		//イベントハンドラの取得
		auto event = CreateEvent(nullptr, false, false, nullptr);
		//イベントのセット
		mFence->SetEventOnCompletion(mFenceVal, event);
		//イベントが発生するまで待つ
		WaitForSingleObject(event, INFINITE);
		//イベントハンドラを閉じる
		CloseHandle(event);
	}
}

//その他
void HDL_Renderer::EnableDebugLayer() 
{
	ComPtr<ID3D12Debug>	debugLayer = nullptr;
	auto result = D3D12GetDebugInterface(IID_PPV_ARGS(debugLayer.ReleaseAndGetAddressOf()));

	if (FAILED(result))
	{
		std::cout << "デバックレイヤーの生成に失敗" << std::endl;
		return;
	}

	debugLayer->EnableDebugLayer();
	debugLayer.Reset();
}