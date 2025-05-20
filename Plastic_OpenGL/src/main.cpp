#include "plastic_opengl_class.h"

int main() {
    OpenGLClass opengl;
    if (opengl.Initalize() != 0) {
        return -1;
    }
    while (!glfwWindowShouldClose(opengl.GetWindow())) {
        opengl.Render();
        glfwSwapBuffers(opengl.GetWindow());
        glfwPollEvents();
    }
    opengl.Shutdown();
}