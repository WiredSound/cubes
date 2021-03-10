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

    bool Chunk::is_no_block_at(const glm::uvec3& pos) const {
        return get_block(pos) == Block::None;
    }

    gfx::Mesh Chunk::build_simple_mesh(
        float face_size,
        optional_chunk_ref above_chunk, optional_chunk_ref below_chunk,
        optional_chunk_ref left_chunk, optional_chunk_ref right_chunk,
        optional_chunk_ref front_chunk, optional_chunk_ref rear_chunk
    ) const {
        return SimpleChunkMeshBuilder(
            face_size, *this,
            above_chunk, below_chunk,
            left_chunk, right_chunk,
            front_chunk, rear_chunk
        ).build();
    }

    //util::Mesh Chunk::build_greedy_mesh(float face_size) const {}

    std::size_t Chunk::pos_to_array_index(const glm::uvec3& pos) const {
        return std::clamp((CHUNK_LENGTH * pos.z + pos.y) * CHUNK_LENGTH + pos.x, 0u, CHUNK_SIZE - 1);
    }
}
