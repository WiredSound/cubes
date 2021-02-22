#include <glad/glad.h>

#include <stdexcept>
#include <iostream>

#include "window.hpp"

Window::~Window() {
    if(handle != nullptr) {
        glfwDestroyWindow(handle);
        std::cout << "Window destroyed" << std::endl;
    }
}

void Window::create(int width, int height, const char* title) {
    handle = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if(handle == nullptr) {
        throw std::runtime_error("Failed to create GLFW window");
    }

    // Resize OpenGL viewport on window resize:
    glfwSetFramebufferSizeCallback(
        handle,
        []([[maybe_unused]] GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }
    );

    glfwMakeContextCurrent(handle);

    std::cout << "Window created" << std::endl;
}

bool Window::should_stay_open() {
    return !glfwWindowShouldClose(handle);
}

void Window::close() {
    glfwSetWindowShouldClose(handle, true);
}

void Window::draw_and_update() {
    glfwSwapBuffers(handle);
    glfwPollEvents();
}

bool Window::is_key_down(int key) {
    return glfwGetKey(handle, key) == GLFW_PRESS;
}

bool Window::was_key_just_pressed(int key) {
    bool result = false;

    if(glfwGetKey(handle, key) == GLFW_PRESS) {
        if(down_keys.find(key) == down_keys.end()) {
            result = true;
            down_keys.insert(key);
        }
    }
    else {
        down_keys.erase(key);
    }

    return result;
}
