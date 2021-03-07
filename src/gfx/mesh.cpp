#include <glad/glad.h>

#include "gfx/mesh.hpp"

namespace gfx {
    Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, int vertex_count)
        : vertices_vbo(GL_ARRAY_BUFFER, false), indices_vbo(GL_ELEMENT_ARRAY_BUFFER, false), vertex_count(vertex_count) {
        // TODO: Fill buffers and VAO with provided data.
    }

    void Mesh::bind_and_draw() const {
        vao.bind();
        glDrawElements(GL_TRIANGLES, vertex_count, GL_UNSIGNED_INT, 0);
    }
}
