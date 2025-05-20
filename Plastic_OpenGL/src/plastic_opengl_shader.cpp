#include "plastic_opengl_shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ShaderClass::ShaderClass() {
    shaderProgram = 0;
    vertexShader = 0;
    fragmentShader = 0;
}

ShaderClass::~ShaderClass() {
<<<<<<< HEAD
=======
    // Destructor
>>>>>>> 6232b88ed33750aa027905df3895dfed9f42780c
    Shutdown();
}

int ShaderClass::Initialize(const char* vertexPath, const char* fragmentPath) {
    // Load and compile vertex shader
    std::string vertexCode;
    std::ifstream vShaderFile(vertexPath);
    if (vShaderFile) {
        std::stringstream vShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        vertexCode = vShaderStream.str();
    } else {
        std::cerr << "Failed to open vertex shader file" << std::endl;
        return -1;
    }
    vShaderFile.close();

    const char* vShaderCode = vertexCode.c_str();
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);

    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "Vertex Shader Compilation Error: " << infoLog << std::endl;
        return -1;
    }

    // Load and compile fragment shader
    std::string fragmentCode;
    std::ifstream fShaderFile(fragmentPath);
    if (fShaderFile) {
        std::stringstream fShaderStream;
        fShaderStream << fShaderFile.rdbuf();
        fragmentCode = fShaderStream.str();
    } else {
        std::cerr << "Failed to open fragment shader file" << std::endl;
        return -1;
    }
    fShaderFile.close();

    const char* fShaderCode = fragmentCode.c_str();
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "Fragment Shader Compilation Error: " << infoLog << std::endl;
        return -1;
    }

    // Link shaders into a program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "Shader Program Linking Error: " << infoLog << std::endl;
        return -1;
    }

    // Delete shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return 0;
}

// New method to set projection and view matrices
void ShaderClass::SetMatrices(const glm::mat4& projection, const glm::mat4& view) {
    glUseProgram(shaderProgram);

    int projLoc = glGetUniformLocation(shaderProgram, "projection");
    int viewLoc = glGetUniformLocation(shaderProgram, "view");

    if (projLoc == -1) {
        std::cerr << "Warning: 'projection' uniform not found in shader.\n";
    } else {
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    }

    if (viewLoc == -1) {
        std::cerr << "Warning: 'view' uniform not found in shader.\n";
    } else {
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    }
}

void ShaderClass::Shutdown() {
    glDeleteProgram(shaderProgram);
}
