#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <stdexcept>

#include "init.hpp"

void init_glfw() {
    if(!glfwInit()) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialise GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
}

void init_gl() {
    if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw std::runtime_error("Failed to initialise GLAD");
    }
}
