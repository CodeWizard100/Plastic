#pragma once
#include "plastic_opengl.h"

class ShaderClass {
public:
    ShaderClass();
    ~ShaderClass();

    int Initialize(const char* vertexPath, const char* fragmentPath);
    void Shutdown();
    GLuint GetShaderProgram() { return shaderProgram; }
    GLuint GetVertexShader() { return vertexShader; }
    GLuint GetFragmentShader() { return fragmentShader; }
    void SetMatrices(const glm::mat4& projection, const glm::mat4& view);
private:
    GLuint shaderProgram;
    GLuint vertexShader;
    GLuint fragmentShader;

};