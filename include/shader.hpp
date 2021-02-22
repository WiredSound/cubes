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
    void attach(Shader shader) const;
    void link() const;
    void use() const;

private:
    unsigned int id;
};
