#include <glad/glad.h>

#include <fstream>
#include <memory>
#include <stdexcept>
#include <sstream>

#include "log.hpp"
#include "gfx/shader.hpp"

namespace gfx {
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

        LOG("Compiled shader " << id);
    }

    Shader::~Shader() {
        glDeleteShader(id);
        LOG("Deleted shader " << id);
    }

    unsigned int Shader::operator*() const {
        return id;
    }

    ShaderProgram::ShaderProgram() {
        id = glCreateProgram();
        LOG("Created shader program " << id);
    }

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(id);
        LOG("Deleted shader program " << id);
    }

    void ShaderProgram::attach(const Shader& shader) const {
        glAttachShader(id, *shader);
        LOG("Attached shader " << *shader << " to shader program " << id);
    }

    void ShaderProgram::link() const {
        glLinkProgram(id);

        int success;
        glGetProgramiv(id, GL_LINK_STATUS, &success);

        if(success) {
            LOG("Linked shader program " << id);
        }
        else {
            char info[512];
            glGetProgramInfoLog(id, 512, nullptr, info);

            throw std::runtime_error(std::string("Failed to link shader program due to error: ") + info);
        }
    }

    void ShaderProgram::use() const {
        glUseProgram(id);
    }

    void ShaderProgram::set_uniform(const std::string& key, const glm::mat4& value) const {
        //use();
        glUniformMatrix4fv(glGetUniformLocation(id, key.c_str()), 1, false, &value[0][0]);
    }
}
