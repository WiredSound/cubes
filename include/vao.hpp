#pragma once

#include <glad/glad.h>

#include "vbo.hpp"

class VertexArrayObject {
public:
    VertexArrayObject();
    ~VertexArrayObject();
    void bind() const;
    void attribute(const VertexBufferObject& buffer, unsigned int index, int size, GLenum type) const;

private:
    unsigned int id;
};
