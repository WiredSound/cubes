#pragma once

#include <glm/glm.hpp>

#include <cstddef>
#include <array>
#include <vector>

#include "world/block.hpp"
#include "gfx/mesh.hpp"

namespace world {
    /// Width, depth, height of a single chunk.
    const unsigned int CHUNK_LENGTH = 32;
    /// Number of blocks per chunk.
    const unsigned int CHUNK_SIZE = CHUNK_LENGTH * CHUNK_LENGTH * CHUNK_LENGTH;

    class Chunk {
    public:
        Chunk(Block fill_block = Block::None);

        void set_block(Block b, const glm::uvec3& pos);
        Block get_block(const glm::uvec3& pos) const;

        gfx::Mesh build_simple_mesh(float face_size) const;
        //gfx::Mesh build_greedy_mesh(float face_size) const;

    private:
        std::size_t pos_to_array_index(const glm::uvec3& pos) const;

        std::array<Block, CHUNK_SIZE> blocks;
    };
}
