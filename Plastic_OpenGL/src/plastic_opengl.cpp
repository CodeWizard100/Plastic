#include "plastic_opengl.h"
#include "plastic_opengl_glfwinput.h"
#ifndef PLASTIC_GL_API
#error "plastic_core.h not included!"
#endif
int _plastic_opengl_glfw_init() {
    if (PLASTIC_GL_MSAA) {
        glfwWindowHint(GLFW_SAMPLES, PLASTIC_GL_MSAA_COUNT);
    } else {
        glfwWindowHint(GLFW_SAMPLES, 0);
    }


    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    int refreshRate = 0; // yes, 0
    GLFWmonitor* monitor = nullptr;
    int width = PLASTIC_GL_WIDTH;
    int height = PLASTIC_GL_HEIGHT;
    if (PLASTIC_GL_FULLSCREEN) {
        monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        width = mode->width;
        height = mode->height;
        refreshRate = mode->refreshRate;
        glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
        glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
       
    }

    window = glfwCreateWindow(width, height, PLASTIC_GL_APPNAME, nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }

    if (PLASTIC_GL_FULLSCREEN || PLASTIC_GL_BORDERLESS) {
        glfwSetWindowMonitor(window,monitor, 0, 0, width, height, refreshRate); // fullscreen toggle
    }

    glfwMakeContextCurrent(window);

    if (PLASTIC_GL_VSYNC) {
        glfwSwapInterval(1);
    } else {
        glfwSwapInterval(0);
    }
    return 0;
}
PLASTIC_GL_API int plastic_opengl_init() {
    if (!glfwInit()) return -1;

    if (_plastic_opengl_glfw_init() != 0) return -2;
    // Set the key callback
    glfwSetKeyCallback(window, key_callback);
    
    return 0;
}


PLASTIC_GL_API void plastic_opengl_shutdown() {
    glfwDestroyWindow(window);
    glfwTerminate();
}
PLASTIC_GL_API void plastic_opengl_render() {

}

PLASTIC_GL_API void plastic_opengl_update() {
    plastic_opengl_render();
    glfwPollEvents();
}
GLFWwindow* window = nullptr;
