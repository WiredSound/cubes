#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <iostream>
#include <stdexcept>

#include "init.hpp"
#include "window.hpp"
#include "shader.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main() {
    Window window;

    try {
        init_glfw();

        window.create(800, 600, "OpenGL Template C++");
        glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback);

        init_gl();
    }
    catch(std::exception& err) {
        std::cerr << "Initialisation failed - " << err.what() << std::endl;
        return -1;
    }

    ShaderProgram program;

    try {
        Shader vert("test.vert", ShaderType::Vertex);
        Shader frag("test.frag", ShaderType::Fragment);

        program.attach(vert);
        program.attach(frag);

        program.link();
    }
    catch(std::exception& err) {
        std::cerr << "Shader program construction failed - " << err.what() << std::endl;
        return -1;
    }

    program.use();

    while(!glfwWindowShouldClose(*window)) {
        if(glfwGetKey(*window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(*window, true);
        }

        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(*window);
        glfwPollEvents();
    }

    return 0;
}

void framebuffer_size_callback([[maybe_unused]] GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
