#pragma once

/// Initialise GLFW. Must called before creating a window.
void init_glfw();

/// Initialise OpenGL via GLAD. May only be called after GLFW has been initialised.
void init_gl();
