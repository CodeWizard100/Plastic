#include "plastic_opengl.h"
#include "plastic_opengl_shader.h"
class OpenGLClass {
public:
    OpenGLClass();
    ~OpenGLClass();

    int Initalize();
    void Render();
    void Shutdown();
    GLFWwindow* GetWindow() { return window; }
        static constexpr float vertices[9] = {
        -0.5f, -0.5f, 0.0f,  
        0.5f, -0.5f, 0.0f,  
        0.0f,  0.5f, 0.0f   
    };

    static constexpr unsigned int indices[3] = { 0, 1, 2 };
    GLuint GetVAO() { return VAO; }
    GLuint GetVBO() { return VBO; }
    GLuint GetEBO() { return EBO; }
    
private:
    GLFWwindow* window;
    GLuint VAO, VBO, EBO;
    ShaderClass shader;

};
