#include "plastic_dx.h"
#include "plastic_dx_class.h"
#include "plastic_dx_glfwinput.h"
#include "plastic_camera.h"
#include "plastic_model_class.h"
#include "plastic_shader_class.h"
#include <chrono>
#include "loadxml.h"

#ifndef PLASTIC_DX_API
#error "plastic_core.h not included!"
#endif

D3DClass* m_Direct3D; // Private Direct3D object
CameraClass* m_Camera;
ModelClass* m_Model;
ColorShaderClass* m_ColorShader;

int _plastic_dx_glfw_init() {
    if (PLASTIC_DX_MSAA) {
        glfwWindowHint(GLFW_SAMPLES, PLASTIC_DX_MSAA_COUNT);
    } else {
        glfwWindowHint(GLFW_SAMPLES, 0);
    }


    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    int refreshRate = 0; // yes, 0
    GLFWmonitor* monitor = nullptr;
    int width = PLASTIC_DX_WIDTH;
    int height = PLASTIC_DX_HEIGHT;
    if (PLASTIC_DX_FULLSCREEN) {
        monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        width = mode->width;
        height = mode->height;
        refreshRate = mode->refreshRate;
        glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
        glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
       
    }

    window = glfwCreateWindow(width, height, PLASTIC_DX_APPNAME, nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }

    if (PLASTIC_DX_FULLSCREEN || PLASTIC_DX_BORDERLESS) {
        glfwSetWindowMonitor(window,monitor, 0, 0, width, height, refreshRate); // fullscreen toggle
    }

    glfwMakeContextCurrent(window);

    if (PLASTIC_DX_VSYNC) {
        glfwSwapInterval(1);
    } else {
        glfwSwapInterval(0);
    }
    return 0;
}
int _plastic_dx_directx_init() {
    m_Direct3D = new D3DClass();
    m_Camera = new CameraClass();
	m_Model = new ModelClass();
	m_ColorShader = new ColorShaderClass();
    bool result = m_Direct3D->Initialize(PLASTIC_DX_WIDTH, PLASTIC_DX_HEIGHT, PLASTIC_DX_VSYNC, glfwGetWin32Window(window), PLASTIC_DX_FULLSCREEN, 0.1f, 1000.0f, PLASTIC_DX_MSAA == 1, PLASTIC_DX_MSAA_COUNT, PLASTIC_DX_MSAA_QUALITY);
    if (!result) {
        std::cerr << "Failed to initialize Direct3D" << std::endl;
        return 1;
    }

    // Create the camera object.
	m_Camera = new CameraClass;

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -5.0f);

	// Create and initialize the model object.
	m_Model = new ModelClass;

	result = m_Model->Initialize(m_Direct3D->GetDevice());
	if(!result)
	{
		std::cerr << "Could not initialize the model object." << std::endl;
		return 1;
	}

	// Create and initialize the color shader object.
	m_ColorShader = new ColorShaderClass;

	result = m_ColorShader->Initialize(m_Direct3D->GetDevice(), glfwGetWin32Window(window));
	if(!result)
	{
		std::cerr << "Could not initialize the color shader object." << std::endl;
		return 1;
	}


    return 0;
}
PLASTIC_DX_API int plastic_dx_init() {
    loadxml(&PLASTIC_DX_WIDTH, &PLASTIC_DX_HEIGHT, &PLASTIC_DX_FULLSCREEN, &PLASTIC_DX_BORDERLESS, &PLASTIC_DX_VSYNC, &PLASTIC_DX_MSAA, &PLASTIC_DX_MSAA_COUNT, &PLASTIC_DX_MSAA_QUALITY);
    if (!glfwInit()) return -1;

    if (_plastic_dx_glfw_init() != 0) return -2;
        
    if (_plastic_dx_directx_init() != 0) return -3;
    // Set the key callback
    glfwSetKeyCallback(window, key_callback);
    
    return 0;
}
void _get_deltaTime(float& deltaTime) {
    static auto lastTime = std::chrono::high_resolution_clock::now();
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = currentTime - lastTime;
    deltaTime = elapsed.count();
    lastTime = currentTime;
}
PLASTIC_DX_API void plastic_dx_shutdown() {
    
	// Release the color shader object.
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	// Release the model object.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}
    
    if (m_Direct3D) {
        m_Direct3D->Shutdown();
        delete m_Direct3D;
        m_Direct3D = nullptr;
    }
    glfwDestroyWindow(window);
    glfwTerminate();
}
PLASTIC_DX_API void plastic_dx_render() {
    if (m_Direct3D) {


	    m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
        m_Camera->Render();
        float deltaTime = 0.0f;
        _get_deltaTime(deltaTime);

        XMMATRIX viewMatrix, projectionMatrix;
       // Rotate by a small amount per frame (e.g., 1 degree per frame)
        // Rotation speed in degrees per second
        float degreesPerSecond = 90.0f; // rotate 90 degrees per second

        // Convert to radians and multiply by delta time to make it frame-independent
        float rotationSpeed = XMConvertToRadians(degreesPerSecond) * deltaTime;

        // Compute rotation matrix
        XMMATRIX rotation = XMMatrixRotationY(rotationSpeed);

        // Apply rotation to current world matrix
        XMMATRIX currentWorld = m_Model->GetWorldMatrix();
        m_Model->SetWorldMatrix(rotation * currentWorld);


        m_Camera->GetViewMatrix(viewMatrix);
        m_Direct3D->GetProjectionMatrix(projectionMatrix);
        m_Model->Render(m_Direct3D->GetDeviceContext());
        m_ColorShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), m_Model->GetWorldMatrix(), viewMatrix, projectionMatrix);
        
	    m_Direct3D->EndScene();


    } else {
        throw std::runtime_error("Direct3D not initialized");
    }

  
}

PLASTIC_DX_API void plastic_dx_update() {
    plastic_dx_render();
    glfwPollEvents();
}
GLFWwindow* window = nullptr;
