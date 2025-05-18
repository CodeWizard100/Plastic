#pragma once
#include <GLFW/glfw3.h>
// INCLUDES
#include "plastic_core.h"


// NAMESPACE

// DEFINTIONS
PLASTIC_GL_API int plastic_opengl_init();
PLASTIC_GL_API void plastic_opengl_shutdown();
PLASTIC_GL_API void plastic_opengl_update();
PLASTIC_GL_API void plastic_opengl_render();

static const char* PLASTIC_GL_VERSION = "0.0.1";
static const char* PLASTIC_GL_APPNAME = "Plastic OpenGL";
static int PLASTIC_GL_WIDTH = 1280;
static int PLASTIC_GL_HEIGHT = 720;
static int PLASTIC_GL_FULLSCREEN = 0;
static int PLASTIC_GL_BORDERLESS = 0;
static int PLASTIC_GL_VSYNC = 1;
static int PLASTIC_GL_MSAA = 1;
static int PLASTIC_GL_MSAA_COUNT = 4;

extern GLFWwindow* window; 