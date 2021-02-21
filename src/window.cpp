#include "window.hpp"

#include <stdexcept>

void Window::create(int width, int height, const char* title) {
    handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if(handle == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(handle);
}

GLFWwindow* Window::operator*() {
    return handle;
}

Window::~Window() {
    glfwTerminate();
}
