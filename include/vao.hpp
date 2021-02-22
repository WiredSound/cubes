#pragma once

#include <glad/glad.h>

class VertexArrayObject {
public:
    VertexArrayObject();
    ~VertexArrayObject();
    void bind();
    void attribute(VertexBufferObject buffer, unsigned int index, int size, GLenum type);

private:
    unsigned int id;
};
