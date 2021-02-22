#include <iostream>

#include "gfx/vbo.hpp"

namespace gfx {
    VertexBuffer::VertexBuffer(GLenum type, bool dynamic) : type(type), dynamic(dynamic) {
        glGenBuffers(1, &id);
        std::cout << "Generated VBO " << id << std::endl;
    }

    VertexBuffer::~VertexBuffer() {
        glDeleteBuffers(1, &id);
        std::cout << "Deleted VBO " << id << std::endl;
    }

    unsigned int VertexBuffer::operator*() const {
        return id;
    }

    void VertexBuffer::bind() const {
        glBindBuffer(type, id);
    }
}
