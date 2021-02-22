#pragma once

#include <GLFW/glfw3.h>

/// Wrapper around a `GLFWwindow` object. Automatically calls `glfwDestroyWindow` on destruction.
class Window {
public:
    /// Creates a window with the specified dimensions and title. Will throw `std::runtime_error` should GLFW fail to
    /// create the window.
    void create(int width, int height, const char* title);
    GLFWwindow* operator*() const;
    ~Window();

private:
    GLFWwindow* handle;
};
