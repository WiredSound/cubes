#include "window.hpp"

#include <stdexcept>
#include <iostream>

void Window::create(int width, int height, const char* title) {
    handle = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if(handle == nullptr) {
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(handle);

    std::cout << "Window created" << std::endl;
}

GLFWwindow* Window::operator*() const {
    return handle;
}

Window::~Window() {
    glfwDestroyWindow(handle);
    std::cout << "Window destroyed" << std::endl;
}
