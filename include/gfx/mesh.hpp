#pragma once

#include <cstddef>
#include <vector>

#include "gfx/vao.hpp"
#include "gfx/vbo.hpp"

namespace gfx {
    class Mesh {
    public:
        Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, int vertex_count);
        void bind_and_draw() const;

    private:
        VertexArray vao;
        VertexBuffer vertices_vbo;
        VertexBuffer indices_vbo;
        const unsigned int vertex_count;
    };
}
