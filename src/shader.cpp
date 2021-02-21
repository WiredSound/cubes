#include <glad/glad.h>

#include <fstream>
#include <memory>
#include <stdexcept>
#include <sstream>

#include "shader.hpp"

Shader::Shader(const std::string& path, ShaderType type) {
    std::ifstream file(path.c_str());

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    std::stringstream buffer;
    buffer << file.rdbuf();
    auto shader = buffer.str();

    switch(type) {
        case ShaderType::Vertex: id = glCreateShader(GL_VERTEX_SHADER); break;
        case ShaderType::Fragment: id = glCreateShader(GL_FRAGMENT_SHADER); break;
    }

    auto shader_c_str = shader.c_str();
    glShaderSource(id, 1, &shader_c_str, nullptr);
    glCompileShader(id);

    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if(!success) {
        char info[512];
        glGetShaderInfoLog(id, 512, nullptr, info);

        auto msg = std::string("Failed to compile shader from path '") +  path + std::string("' due to error: ") + info;
        throw std::runtime_error(msg);
    }
}
