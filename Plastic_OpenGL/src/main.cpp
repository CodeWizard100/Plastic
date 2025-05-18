#include "plastic_opengl.h"
#include <iostream>

int main() {

    if (plastic_opengl_init() != 0) {
        std::cerr << "Failed to initialize Plastic OpenGL" << std::endl;
        return -1;
    }
    while (!glfwWindowShouldClose(window)) {
        plastic_opengl_update();
      
    }
    plastic_opengl_shutdown();
    return 0;
}
 