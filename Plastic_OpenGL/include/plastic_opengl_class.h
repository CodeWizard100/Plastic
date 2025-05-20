#pragma once
#include "plastic_opengl.h"

class OpenGLClass {
    public:
        int Initalize();
        void Render();
        void Shutdown();
        bool initalized = false;
    private:
        GLuint VBO, VAO, EBO;
        GLuint shaderProgram;
};