#include <iostream>

#include "vbo.hpp"

VertexBufferObject::VertexBufferObject(GLenum type, bool dynamic) : type(type), dynamic(dynamic) {
    glGenBuffers(1, &id);
    std::cout << "Generated VBO " << id << std::endl;
}

VertexBufferObject::~VertexBufferObject() {
    glDeleteBuffers(1, &id);
    std::cout << "Deleted VBO " << id << std::endl;
}

unsigned int VertexBufferObject::operator*() const {
    return id;
}

void VertexBufferObject::bind() const {
    glBindBuffer(type, id);
}
