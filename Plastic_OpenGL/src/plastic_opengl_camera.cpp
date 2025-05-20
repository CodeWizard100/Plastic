#include "plastic_opengl_camera.h"
/*

CameraClass::CameraClass() {
    
}
CameraClass::~CameraClass() {
    
}
int CameraClass::Initalize(ShaderClass* shaderclass) {
    this->shader = shaderclass;
    return 0;
}

void CameraClass::SetCameraPosition(float x, float y, float z) {
    // Set camera position
    glm::vec3 cameraPos(x, y, z);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), -cameraPos);
    shader->SetMatrices(glm::mat4(1.0f), view);
}
void CameraClass::SetCameraRotation(float angle, float x, float y, float z) {
    // Set camera rotation
    glm::mat4 view = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(x, y, z));
    shader->SetMatrices(glm::mat4(1.0f), view);
}
void CameraClass::SetCameraScale(float scale) {
    // Set camera scale
    glm::mat4 view = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
    shader->SetMatrices(glm::mat4(1.0f), view);
}
*/