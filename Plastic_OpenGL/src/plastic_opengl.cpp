#include "plastic_opengl.h"
#include "plastic_opengl_glfwinput.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef PLASTIC_GL_API
#error "plastic_core.h not included!"
#endif
float vertices[] = {
    // Positions (x, y, z)
    -0.5f, -0.5f, -0.5f,  // 0: left-bottom-back
     0.5f, -0.5f, -0.5f,  // 1: right-bottom-back
     0.5f,  0.5f, -0.5f,  // 2: right-top-back
    -0.5f,  0.5f, -0.5f,  // 3: left-top-back
    -0.5f, -0.5f,  0.5f,  // 4: left-bottom-front
     0.5f, -0.5f,  0.5f,  // 5: right-bottom-front
     0.5f,  0.5f,  0.5f,  // 6: right-top-front
    -0.5f,  0.5f,  0.5f   // 7: left-top-front
};

unsigned int indices[] = {
    // Back face
    0, 1, 2,
    2, 3, 0,

    // Front face
    4, 5, 6,
    6, 7, 4,

    // Left face
    4, 7, 3,
    3, 0, 4,

    // Right face
    1, 5, 6,
    6, 2, 1,

    // Bottom face
    0, 1, 5,
    5, 4, 0,

    // Top face
    3, 2, 6,
    6, 7, 3
};
const char *vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(aPos, 1.0);
}
)";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\n\0";

unsigned int VBO, VAO, EBO;
unsigned int shaderProgram;
int _plastic_opengl_glfw_init() {
    if (PLASTIC_GL_MSAA) {
        glfwWindowHint(GLFW_SAMPLES, PLASTIC_GL_MSAA_COUNT);
    } else {
        glfwWindowHint(GLFW_SAMPLES, 0);
    }
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    int refreshRate = 0; // yes, 0
    GLFWmonitor* monitor = nullptr;
    int width = PLASTIC_GL_WIDTH;
    int height = PLASTIC_GL_HEIGHT;
    if (PLASTIC_GL_FULLSCREEN) {
        monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        width = mode->width;
        height = mode->height;
        refreshRate = mode->refreshRate;
        glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
        glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
       
    }

    window = glfwCreateWindow(width, height, PLASTIC_GL_APPNAME, nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }

    if (PLASTIC_GL_FULLSCREEN || PLASTIC_GL_BORDERLESS) {
        glfwSetWindowMonitor(window,monitor, 0, 0, width, height, refreshRate); // fullscreen toggle
    }

    glfwMakeContextCurrent(window);

    if (PLASTIC_GL_VSYNC) {
        glfwSwapInterval(1);
    } else {
        glfwSwapInterval(0);
    }
    return 0;
}
int _plastic_opengl_init_gl() {
      if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }   
    // Build and compile our shader program
    unsigned int vertexShader, fragmentShader;
    int success;
    char infoLog[512];

    // Vertex Shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // Print compile errors if any
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return -1;
    }
    
    // Fragment Shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // Print compile errors if any
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return -2;
    }

    // Link shaders
    
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return 0;
}
PLASTIC_GL_API int plastic_opengl_init() {
    loadxml(&PLASTIC_GL_WIDTH, &PLASTIC_GL_HEIGHT, &PLASTIC_GL_FULLSCREEN, &PLASTIC_GL_BORDERLESS, &PLASTIC_GL_VSYNC, &PLASTIC_GL_MSAA, &PLASTIC_GL_MSAA_COUNT, &PLASTIC_GL_MSAA_QUALITY);
    if (!glfwInit()) return -1;

    if (_plastic_opengl_glfw_init() != 0) return -2;
    if (_plastic_opengl_init_gl() != 0) return -3;
    // Set the viewport
    glViewport(0, 0, PLASTIC_GL_WIDTH, PLASTIC_GL_HEIGHT);
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
     glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 
    
    // Set the key callback
    glfwSetKeyCallback(window, key_callback);
    
    return 0;
}


PLASTIC_GL_API void plastic_opengl_shutdown() {
    glfwDestroyWindow(window);
    glfwTerminate();
}
PLASTIC_GL_API void plastic_opengl_render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float time = glfwGetTime(); // seconds since start
    glm::mat4 model = glm::rotate(glm::mat4(90.0f * time), time, glm::vec3(0.0f, 90.0f * time, 0.0f));

    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 2.5f),
                                 glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                            (float)PLASTIC_GL_WIDTH / (float)PLASTIC_GL_HEIGHT,
                                            0.1f, 100.0f);
                                            
    glm::mat4 mvp = projection * view * model;

    glUseProgram(shaderProgram);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "MVP"), 1, GL_FALSE, glm::value_ptr(mvp));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);
}

PLASTIC_GL_API void plastic_opengl_update() {
    plastic_opengl_render();

    glfwSwapBuffers(window);
    glfwPollEvents();
    
}
GLFWwindow* window = nullptr;
