#pragma once

#include <string>

enum struct ShaderType { Vertex, Fragment };

class Shader {
public:
    Shader(const std::string& path, ShaderType type);

private:
    unsigned int id;
};
