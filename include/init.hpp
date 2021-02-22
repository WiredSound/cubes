#pragma once

/// Handles the initialisation of GLFW. Will call `glfwTerminate` when destroyed.
class InitGLFW {
public:
    void init();
    ~InitGLFW();
};

/// Initialise OpenGL via GLAD. May only be called after GLFW has been initialised and a window has been created.
void init_gl();
