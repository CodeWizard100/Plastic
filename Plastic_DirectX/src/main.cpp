#include "plastic_dx.h"


int main() {

    if (plastic_dx_init() != 0) {
        std::cerr << "Failed to initialize Plastic DirectX" << std::endl;
        return -1;
    }
    while (!glfwWindowShouldClose(window)) {
        plastic_dx_update();
      
    }
    plastic_dx_shutdown();
    return 0;
}
 