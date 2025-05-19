#pragma once
#ifndef GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#endif
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>   // must come *after* glfw3.h

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
PLASTIC_DX_API int plastic_dx_init();
PLASTIC_DX_API void plastic_dx_shutdown();
PLASTIC_DX_API void plastic_dx_update();
PLASTIC_DX_API void plastic_dx_render();

static const char* PLASTIC_DX_VERSION = "0.0.1";
static const char* PLASTIC_DX_APPNAME = "Plastic DirectX";
static int PLASTIC_DX_WIDTH = 1280;
static int PLASTIC_DX_HEIGHT = 720;
static int PLASTIC_DX_FULLSCREEN = 0;
static int PLASTIC_DX_BORDERLESS = 1;
static int PLASTIC_DX_VSYNC = 1;
static int PLASTIC_DX_MSAA = 0;
static int PLASTIC_DX_MSAA_COUNT = 4;
static int PLASTIC_DX_MSAA_QUALITY = 1;
extern GLFWwindow* window; 