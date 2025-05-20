#include "plastic_opengl_class.h"
constexpr float OpenGLClass::vertices[9];
constexpr unsigned int OpenGLClass::indices[3];

OpenGLClass::OpenGLClass() {
    // Constructor
}
OpenGLClass::~OpenGLClass() {
    // Destructor
    Shutdown();
}



int OpenGLClass::Initalize() {
    std::cout << a;
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set GLFW window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(PLASTIC_GL_WIDTH, PLASTIC_GL_HEIGHT, PLASTIC_GL_APPNAME, NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    

    // Set viewport
    glViewport(0, 0, PLASTIC_GL_WIDTH, PLASTIC_GL_HEIGHT);

    // Set up shaders
    
    if (shader.Initialize("vertex_shader.glsl", "fragment_shader.glsl") != 0) {
        #ifdef ENABLE_FALLBACK
        if (shader.Initialize((std::string(FALLBACK_PATH) + "/vertex_shader.glsl").c_str(), (std::string(FALLBACK_PATH) + "/fragment_shader.glsl").c_str() ) != 0) {
            std::cerr << "Failed to initialize shaders" << std::endl;
            return -1;
        }
        #else
        std::cerr << "Failed to initialize shaders" << std::endl;
        return -1;
        #endif
    }  

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)PLASTIC_GL_WIDTH / PLASTIC_GL_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 3.0f),  // camera position
        glm::vec3(0.0f, 0.0f, 0.0f),  // target
        glm::vec3(0.0f, 1.0f, 0.0f)   // up vector
    );

    // Set the matrices uniforms before rendering
    shader.SetMatrices(projection, view);
    //camera.Initalize(&shader);
    
    return 0;
}

void OpenGLClass::Render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shader.GetShaderProgram());

    // Create buffers once
    if (VAO == 0) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
    }

    glBindVertexArray(VAO);

    // Upload new vertex data each frame
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void OpenGLClass::Shutdown() {
    // Cleanup
    shader.Shutdown();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwDestroyWindow(window);
    glfwTerminate();
}