#include "plastic_core.h"
#include "plastic_opengl.h"
#include "plastic_opengl_class.h"
#include <chrono>
#include "loadxml.h"

#ifndef PLASTIC_GL_API
#error "plastic_core.h not included!"
#endif
OpenGLClass openglclass = OpenGLClass();
void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(win, GLFW_TRUE);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
int _plastic_gl_glfw_init() {
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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (PLASTIC_GL_VSYNC) {
        glfwSwapInterval(1);
    } else {
        glfwSwapInterval(0);
    }
    return 0;
}

PLASTIC_GL_API int plastic_gl_init() {
    loadxml(&PLASTIC_GL_WIDTH, &PLASTIC_GL_HEIGHT, &PLASTIC_GL_FULLSCREEN, &PLASTIC_GL_BORDERLESS, &PLASTIC_GL_VSYNC, &PLASTIC_GL_MSAA, &PLASTIC_GL_MSAA_COUNT, &PLASTIC_GL_MSAA_QUALITY);
    if (!glfwInit()) return -1;

    if (_plastic_gl_glfw_init() != 0) return -2;

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -3;
    }

    if (openglclass.Initalize() != 0) {
        std::cerr << "Failed to initalize OpenGL" << std::endl;
        return -4;
    }
    // Set the key callback
    glfwSetKeyCallback(window, key_callback);
    
    return 0;
}

PLASTIC_GL_API void plastic_gl_shutdown() {
    
    openglclass.Shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();
}
PLASTIC_GL_API void plastic_gl_render() {
    // here, we pass it to our class to handle everything for rendering
    if (openglclass.initalized) {
        openglclass.Render();
    } else {
        throw std::runtime_error("OpenGL Not Initalized Before Rendering!");
    }
}

PLASTIC_GL_API void plastic_gl_update() {
    plastic_gl_render();
    glfwSwapBuffers(window);
    glfwPollEvents();
}
GLFWwindow* window = nullptr;
