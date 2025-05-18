#include "plastic_dx.h"
#include "plastic_dx_glfwinput.h"
#ifndef PLASTIC_DX_API
#error "plastic_core.h not included!"
#endif
int _plastic_dx_glfw_init() {
    if (PLASTIC_DX_MSAA) {
        glfwWindowHint(GLFW_SAMPLES, PLASTIC_DX_MSAA_COUNT);
    } else {
        glfwWindowHint(GLFW_SAMPLES, 0);
    }


    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    int refreshRate = 0; // yes, 0
    GLFWmonitor* monitor = nullptr;
    int width = PLASTIC_DX_WIDTH;
    int height = PLASTIC_DX_HEIGHT;
    if (PLASTIC_DX_FULLSCREEN) {
        monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        width = mode->width;
        height = mode->height;
        refreshRate = mode->refreshRate;
        glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
        glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
       
    }

    window = glfwCreateWindow(width, height, PLASTIC_DX_APPNAME, nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }

    if (PLASTIC_DX_FULLSCREEN || PLASTIC_DX_BORDERLESS) {
        glfwSetWindowMonitor(window,monitor, 0, 0, width, height, refreshRate); // fullscreen toggle
    }

    glfwMakeContextCurrent(window);

    if (PLASTIC_DX_VSYNC) {
        glfwSwapInterval(1);
    } else {
        glfwSwapInterval(0);
    }
    return 0;
}
PLASTIC_DX_API int plastic_dx_init() {
    if (!glfwInit()) return -1;

    if (_plastic_dx_glfw_init() != 0) return -2;
    // Set the key callback
    glfwSetKeyCallback(window, key_callback);
    
    return 0;
}


PLASTIC_DX_API void plastic_dx_shutdown() {
    glfwDestroyWindow(window);
    glfwTerminate();
}
PLASTIC_DX_API void plastic_dx_render() {

}

PLASTIC_DX_API void plastic_dx_update() {
    plastic_dx_render();
    glfwPollEvents();
}
GLFWwindow* window = nullptr;
