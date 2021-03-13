#include <glad/glad.h>

#include <cstddef>

#include "util/log.hpp"
#include "world/chunkmesh.hpp"

namespace world {
    ChunkMesh::ChunkMesh() : gfx::Mesh(6) {}

    void ChunkMesh::prepare_attributes(std::size_t stride) {
        vao.attribute(vertices_vbo, 0, 3, GL_FLOAT, stride); // position
        vao.attribute(vertices_vbo, 1, 3, GL_FLOAT, stride, 3 * sizeof(float)); // colour
    }
}
