#pragma once

#include <glm/glm.hpp>

#include <string>

namespace gfx {
    enum struct ShaderType { Vertex, Fragment };

    class Shader {
    public:
        Shader(const std::string& path, ShaderType type);

        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        ~Shader();

        unsigned int operator*() const;

    private:
        unsigned int id;
    };

    class ShaderProgram {
    public:
        ShaderProgram();

        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;

        ~ShaderProgram();

        unsigned int operator*() const;

        void attach(const Shader& shader) const;
        void link() const;
        void use() const;

        void set_uniform(const std::string& key, const glm::vec2& value) const;
        void set_uniform(const std::string& key, const glm::vec3& value) const;
        void set_uniform(const std::string& key, const glm::mat4& value) const;

    private:
        unsigned int id;
    };
}
