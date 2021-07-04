#include <glad/glad.h>

#include <stdexcept>

#include "gfx/window.hpp"
#include "util/log.hpp"

const double CURSOR_LOCK_X = 400.0;
const double CURSOR_LOCK_Y = 300.0;

namespace gfx {
    Window::Window() {}

    Window::~Window() {
        if(handle != nullptr) {
            glfwDestroyWindow(handle);
            LOG("Window " << handle << " destroyed");
        }
    }

    void Window::create(int width, int height, const char* title, bool vsync) {
        this->width = width;
        this->height = height;

        handle = glfwCreateWindow(width, height, title, nullptr, nullptr);

        if(handle == nullptr) {
            throw std::runtime_error("Failed to create GLFW window");
        }

        // TODO: Width, height fields don't update with the resizing of the game window.
        // Overall, the handling of the game window needs a lot of work (e.g. mouse controls don't work very well too).

        // Resize OpenGL viewport on window resize:
        glfwSetFramebufferSizeCallback(
            handle,
            []([[maybe_unused]] GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }
        );

        glfwMakeContextCurrent(handle);

        if(!vsync && glfwExtensionSupported("GLX_EXT_swap_control")) {
            glfwSwapInterval(0);
        }

        LOG("Window " << handle << " created");
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

    void Window::toggle_cursor_lock() {
        cursor_locked = !cursor_locked;

        if(cursor_locked) {
            glfwSetCursorPos(handle, CURSOR_LOCK_X, CURSOR_LOCK_Y);
            glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        }
        else {
            glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }

    glm::vec2 Window::locked_cursor_movement() {
        if(cursor_locked) {
            double x, y;
            glfwGetCursorPos(handle, &x, &y);

            glfwSetCursorPos(handle, CURSOR_LOCK_X, CURSOR_LOCK_Y);

            return glm::vec2(static_cast<float>(x - CURSOR_LOCK_X), static_cast<float>(y - CURSOR_LOCK_Y));
        }
        else return glm::vec2(0.0f, 0.0f);
    }
}
