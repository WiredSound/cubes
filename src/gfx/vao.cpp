#include <iostream>

#include "gfx/vao.hpp"

namespace gfx {
    VertexArray::VertexArray() {
        glGenVertexArrays(1, &id);
        std::cout << "Generated VAO " << id << std::endl;
    }

    VertexArray::~VertexArray() {
        glDeleteVertexArrays(1, &id);
        std::cout << "Deleted VAO " << id << std::endl;
    }

    void VertexArray::bind() const {
        glBindVertexArray(id);
    }

    void VertexArray::attribute(const VertexBuffer& buffer, unsigned int index, int size, GLenum type) const {
        bind();
        buffer.bind();

        // For whatever reason, `glVertexAttribPointer` will implicitly convert integer values to floats. Must use
        // `glVertexAttribIPointer` for integers.
        switch(type) {
        case GL_BYTE: case GL_UNSIGNED_BYTE:
        case GL_SHORT: case GL_UNSIGNED_SHORT:
        case GL_INT: case GL_UNSIGNED_INT:
            glVertexAttribIPointer(
                index, size, type,
                0, // Tightly pack consecutive vertex attributes.
                static_cast<void*>(0) // No offset.
            );
            break;
        default:
            glVertexAttribPointer(
                index, size, type,
                false, // Do not normalise values.
                0, // Tightly pack.
                static_cast<void*>(0) // No offset.
            );
            break;
        }

        glEnableVertexAttribArray(index);
    }
}
