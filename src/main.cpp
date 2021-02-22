#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <iostream>
#include <stdexcept>

#include "init.hpp"
#include "window.hpp"
#include "shader.hpp"
#include "vao.hpp"
#include "vbo.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main() {
    InitGLFW glfw;
    Window window;

    try {
        glfw.init();

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

    VertexBufferObject vbo(GL_ARRAY_BUFFER, false);
    VertexArrayObject vao;

    {
        std::vector vertices = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };
        vbo.data(vertices);
    }

    vao.attribute(vbo, 0, 3, GL_FLOAT);

    while(!glfwWindowShouldClose(*window)) {
        if(glfwGetKey(*window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(*window, true);
        }

        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program.use();
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(*window);
        glfwPollEvents();
    }

    return 0;
}

void framebuffer_size_callback([[maybe_unused]] GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
