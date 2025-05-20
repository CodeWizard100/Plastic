#include "plastic_opengl_class.h"

int OpenGLClass::Initalize() {
    initalized = true;
    return 0;
}

void OpenGLClass::Render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLClass::Shutdown() {

}