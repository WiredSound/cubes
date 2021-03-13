#pragma once

#include <vector>
#include <cstddef>

#include "gfx/vao.hpp"
#include "gfx/vbo.hpp"

namespace gfx {
    class Mesh {
    public:
        Mesh(std::size_t values_per_vertex, bool dynamic = false);
        virtual ~Mesh();

        Mesh(Mesh&&) = default;
        Mesh& operator=(Mesh&&) = default;

        void create(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);

        void bind_and_draw() const;

    protected:
        virtual void prepare_attributes(std::size_t stride) = 0;

        VertexArray vao;

        VertexBuffer vertices_vbo;
        VertexBuffer indices_vbo;

    private:
        std::size_t values_per_vertex;

        unsigned int vertices_count;
        unsigned int indices_count;
    };
}
