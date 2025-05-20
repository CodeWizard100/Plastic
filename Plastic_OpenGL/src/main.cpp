#include "plastic_opengl.h"

int main() {
    if (plastic_gl_init() != 0) {return -1;}
    while (!glfwWindowShouldClose(window)) {
        plastic_gl_update();
    }
    plastic_gl_shutdown();
}