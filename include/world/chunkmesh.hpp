#pragma once

#include <cstddef>
#include <vector>

#include "gfx/vao.hpp"
#include "gfx/vbo.hpp"

namespace world {
    class ChunkMesh {
    public:
        ChunkMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, unsigned int vertex_count);
        void bind_and_draw() const;

    private:
        gfx::VertexArray vao;
        gfx::VertexBuffer vertices_vbo;
        gfx::VertexBuffer indices_vbo;
        const unsigned int vertex_count;
        const unsigned int indices_count;
    };
}
