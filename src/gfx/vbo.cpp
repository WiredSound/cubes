#include "gfx/vbo.hpp"
#include "util/log.hpp"

namespace gfx {
    VertexBuffer::VertexBuffer(GLenum type, bool dynamic) : type(type), dynamic(dynamic) {
        glGenBuffers(1, &id);
        LOG("Generated vertex buffer object " << id);
    }

    VertexBuffer::VertexBuffer(VertexBuffer&& other) : id(other.id), type(other.type), dynamic(other.dynamic) {
        other.id = 0;
    }

    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) {
        id = other.id;
        type = other.type;
        dynamic = other.dynamic;
        other.id = 0;
        return *this;
    }

    VertexBuffer::~VertexBuffer() {
        if(id) {
            glDeleteBuffers(1, &id);
            LOG("Deleted vertex buffer object " << id);
        }
    }

    unsigned int VertexBuffer::operator*() const {
        return id;
    }

    void VertexBuffer::bind() const {
        glBindBuffer(type, id);
    }
}
