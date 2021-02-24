#pragma once

#include <GLFW/glfw3.h>

#include <unordered_set>

/// Wrapper around a `GLFWwindow` object. Automatically calls `glfwDestroyWindow` on destruction.
class Window {
public:
    ~Window();
    /// Creates a window with the specified dimensions and title. Will throw `std::runtime_error` should GLFW fail to
    /// create the window.
    void create(int width, int height, const char* title, bool vsync = true);
    bool should_stay_open();
    void close();
    /// Swap buffers and poll events.
    void draw_and_update();
    bool is_key_down(int key);
    bool was_key_just_pressed(int key);

private:
    GLFWwindow* handle;
    std::unordered_set<int> down_keys;
};
