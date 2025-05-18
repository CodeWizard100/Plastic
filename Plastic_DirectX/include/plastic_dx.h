#pragma once
// LINKER
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
// INCLUDES
#include "plastic_core.h"
#include <iostream>
#include <d3d11.h>
#include <directxmath.h>

// NAMESPACE
using namespace DirectX;

// DEFINTIONS
PLASTIC_DX_API void plastic_dx_init();
PLASTIC_DX_API void plastic_dx_shutdown();
PLASTIC_DX_API void plastic_dx_update();
PLASTIC_DX_API void plastic_dx_render();
