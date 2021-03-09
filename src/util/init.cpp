#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <stdexcept>

#include "util/init.hpp"
#include "util/log.hpp"

namespace util {
    void InitGLFW::init() {
        if(!glfwInit()) {
            glfwTerminate();
            throw std::runtime_error("Failed to initialise GLFW");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);

        LOG("Initialised GLFW");
    }

    InitGLFW::~InitGLFW() {
        glfwTerminate();
        LOG("Terminated GLFW");
    }

    void init_gl() {
        if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            throw std::runtime_error("Failed to initialise GLAD");
        }
        glEnable(GL_DEPTH_TEST);
        LOG("Initialised OpenGL " << GLVersion.major << "." << GLVersion.minor << " via GLAD");
    }
}
