#pragma once

// INCLUDES
#include <iostream>
#include <string>
#include <vector>

#include "plastic_core.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// DEFINTIONS
PLASTIC_GL_API int plastic_dx_init();
PLASTIC_GL_API void plastic_dx_shutdown();
PLASTIC_GL_API void plastic_dx_update();
PLASTIC_GL_API void plastic_dx_render();

static const char* PLASTIC_GL_VERSION = "0.0.1";
static const char* PLASTIC_GL_APPNAME = "Plastic DirectX";
static int PLASTIC_GL_WIDTH = 1280;
static int PLASTIC_GL_HEIGHT = 720;
static int PLASTIC_GL_FULLSCREEN = 0;
static int PLASTIC_GL_BORDERLESS = 1;
static int PLASTIC_GL_VSYNC = 1;
static int PLASTIC_GL_MSAA = 0;
static int PLASTIC_GL_MSAA_COUNT = 4;
static int PLASTIC_GL_MSAA_QUALITY = 1;
#define ENABLE_FALLBACK