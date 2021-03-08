#include <glad/glad.h>

#include <cstddef>

#include "log.hpp"
#include "gfx/mesh.hpp"

namespace gfx {
    Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, int vertex_count)
        : vertices_vbo(GL_ARRAY_BUFFER, false), indices_vbo(GL_ELEMENT_ARRAY_BUFFER, false), vertex_count(vertex_count) {
        vao.bind();

        vertices_vbo.data(vertices);
        indices_vbo.data(indices);

        std::size_t stride = 6 * sizeof(float);
        vao.attribute(vertices_vbo, 0, 3, GL_FLOAT, stride); // position
        vao.attribute(vertices_vbo, 1, 3, GL_FLOAT, stride, 3 * sizeof(float)); // colour

        LOG("Created mesh containing " << vertex_count << " vertices (" << vertices.size() <<
            " floating-point values) and " << indices.size() << " indices");
    }

    void Mesh::bind_and_draw() const {
        vao.bind();
        glDrawElements(GL_TRIANGLES, vertex_count, GL_UNSIGNED_INT, 0);
    }
}
