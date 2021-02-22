#include "log.hpp"
#include "gfx/vbo.hpp"

namespace gfx {
    VertexBuffer::VertexBuffer(GLenum type, bool dynamic) : type(type), dynamic(dynamic) {
        glGenBuffers(1, &id);
        LOG("Generated VBO " << id);
    }

    VertexBuffer::~VertexBuffer() {
        glDeleteBuffers(1, &id);
        LOG("Deleted VBO " << id);
    }

    unsigned int VertexBuffer::operator*() const {
        return id;
    }

    void VertexBuffer::bind() const {
        glBindBuffer(type, id);
    }
}
