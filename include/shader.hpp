#pragma once

#include <string>

enum struct ShaderType { Vertex, Fragment };

class Shader {
public:
    Shader(const std::string& path, ShaderType type);
    ~Shader();
    unsigned int operator*() const;

private:
    unsigned int id;
};

class ShaderProgram {
public:
    ShaderProgram();
    ~ShaderProgram();
    unsigned int operator*() const;
    void attach(const Shader& shader);
    void link();
    void use();

private:
    unsigned int id;
};
