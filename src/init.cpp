#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <stdexcept>
#include <iostream>

#include "init.hpp"

void InitGLFW::init() {
    if(!glfwInit()) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialise GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);

    std::cout << "Initialised GLFW" << std::endl;
}

InitGLFW::~InitGLFW() {
    glfwTerminate();
    std::cout << "Terminated GLFW" << std::endl;
}

void init_gl() {
    if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw std::runtime_error("Failed to initialise GLAD");
    }
    std::cout << "Initialised OpenGL via GLAD" << std::endl;
}
