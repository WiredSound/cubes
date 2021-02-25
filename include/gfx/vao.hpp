#pragma once

#include <glad/glad.h>

#include <cstddef>

#include "gfx/vbo.hpp"

namespace gfx {
    class VertexArray {
    public:
        VertexArray();
        ~VertexArray();
        void bind() const;
        void attribute(const VertexBuffer& buffer, unsigned int index, int size, GLenum type, std::size_t stride,
            std::size_t offset = 0) const;

    private:
        unsigned int id;
    };
}
