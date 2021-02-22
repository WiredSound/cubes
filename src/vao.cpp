#include "vao.hpp"


VertexArrayObject::VertexArrayObject() {
    glGenVertexArrays(1, &array_id);
}

VertexArrayObject::~VertexArrayObject() {
    glDeleteVertexArrays(1, &array_id);
    glDeleteBuffers(buffer_ids.size(), buffer_ids.data());
}

void VertexArrayObject::attribute(VertexBufferObject buffer, unsigned int index, int size, GLenum type) {
    bind();
    buffer.bind();

    // For whatever reason, `glVertexAttribPointer` will implicitly convert integer values to floats. Must use
    // `glVertexAttribIPointer` for integers.
    switch(attrib.type) {
    case GL_BYTE: case GL_UNSIGNED_BYTE:
    case GL_SHORT: case GL_UNSIGNED_SHORT:
    case GL_INT: GL_UNSIGNED_INT:
        glVertexAttribIPointer(
            attrib.index, attrib.size, attrib.type,
            0, // Tightly pack consecutive vertex attributes.
            static_cast<void*>(0) // No offset.
        );
        break;
    default:
        glVertexAttribPointer(
            attrib.index, attrib.size, attrib.type
            false, // Do not normalise values.
            0, // Tightly pack.
            static_cast<void*>(0) // No offset.
        );
        break;
    }

    glEnableVertexAttribArray(attrib.index);
}
