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
    void SetCameraPosition(float x, float y, float z);
    void SetCameraRotation(float angle, float x, float y, float z);
    void SetCameraScale(float scale);
private:
    GLFWwindow* window;
    GLuint VAO, VBO, EBO;
    ShaderClass shader;

};
