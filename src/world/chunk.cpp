#include <algorithm>

#include "world/chunk.hpp"
#include "world/chunkmesh.hpp"

namespace world {
    Chunk::Chunk(Block fill_block) {
        blocks.fill(fill_block);
    }

    void Chunk::set_block(Block b, const glm::uvec3& pos) {
        blocks[pos_to_array_index(pos)] = b;
    }

    Block Chunk::get_block(const glm::uvec3& pos) const {
        return blocks[pos_to_array_index(pos)];
    }

    gfx::Mesh Chunk::build_simple_mesh(float face_size) const {
        return SimpleChunkMeshBuilder(*this, face_size).build();
    }

    //util::Mesh Chunk::build_greedy_mesh(float face_size) const {}

    std::size_t Chunk::pos_to_array_index(const glm::uvec3& pos) const {
        return std::clamp((CHUNK_LENGTH * pos.z + pos.y) * CHUNK_LENGTH + pos.x, 0u, CHUNK_SIZE - 1);
    }
}
