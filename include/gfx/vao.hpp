#pragma once

#include <glad/glad.h>

#include "gfx/vbo.hpp"

namespace gfx {
    class VertexArray {
    public:
        VertexArray();
        ~VertexArray();
        void bind() const;
        void attribute(const VertexBuffer& buffer, unsigned int index, int size, GLenum type) const;

    private:
        unsigned int id;
    };
}
