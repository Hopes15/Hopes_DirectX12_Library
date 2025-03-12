#pragma once
#ifdef _DEBUG
#include <iostream>
#endif

//DirectX12
#include "Assets/d3dx12.h"
#pragma comment (lib, "d3d12.lib")

//ComPtr
#include <wrl.h>
using namespace Microsoft::WRL;

//Asssert
#include <cassert>