#pragma once
#include "plastic_opengl.h"

class OpenGLClass {
    public:
        int Initalize();
        void Render();
        void Shutdown();
    private:
        GLuint VBO, VAO, EBO;
};