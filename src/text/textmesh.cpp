#include "text/textmesh.hpp"

namespace text {
    TextMesh::TextMesh() : gfx::Mesh(4) {}

    void TextMesh::prepare_attributes(std::size_t stride) {
        vao.attribute(vertices_vbo, 0, 2, GL_FLOAT, stride); // position
        vao.attribute(vertices_vbo, 1, 2, GL_FLOAT, stride, 2 * sizeof(float)); // texture coordinates
    }
}
