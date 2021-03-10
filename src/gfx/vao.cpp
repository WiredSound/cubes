#include "gfx/vao.hpp"
#include "util/log.hpp"

namespace gfx {
    VertexArray::VertexArray() {
        glGenVertexArrays(1, &id);
        LOG("Generated vertex array object " << id);
    }

    VertexArray::VertexArray(VertexArray&& other) : id(other.id) {
        other.id = 0;
    }

    VertexArray& VertexArray::operator=(VertexArray&& other) {
        id = other.id;
        other.id = 0;
        return *this;
    }

    VertexArray::~VertexArray() {
        if(id) {
            glDeleteVertexArrays(1, &id);
            LOG("Deleted vertex array object " << id);
        }
    }

    void VertexArray::bind() const {
        glBindVertexArray(id);
    }

    void VertexArray::attribute(
        const VertexBuffer& buffer, unsigned int index, int size, GLenum type, std::size_t stride, std::size_t offset
    ) const {
        bind();
        buffer.bind();

        // For whatever reason, `glVertexAttribPointer` will implicitly convert integer values to floats. Must use
        // `glVertexAttribIPointer` for integers.
        switch(type) {
        case GL_BYTE: case GL_UNSIGNED_BYTE:
        case GL_SHORT: case GL_UNSIGNED_SHORT:
        case GL_INT: case GL_UNSIGNED_INT:
            glVertexAttribIPointer(
                index, size, type, stride, reinterpret_cast<void*>(offset)
            );
            break;
        default:
            glVertexAttribPointer(
                index, size, type,
                false, // Do not normalise values.
                stride, reinterpret_cast<void*>(offset)
            );
            break;
        }

        glEnableVertexAttribArray(index);
    }
}
