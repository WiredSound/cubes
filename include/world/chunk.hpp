#pragma once

#include <glm/glm.hpp>

#include <cstddef>
#include <array>
#include <vector>

#include "world/block.hpp"

namespace world {
    /// Width, depth, height of a single chunk.
    const unsigned int CHUNK_LENGTH = 32;
    /// Number of blocks per chunk.
    const unsigned int CHUNK_SIZE = CHUNK_LENGTH * CHUNK_LENGTH * CHUNK_LENGTH;

    class Chunk {
    public:
        Chunk(Block fill_block = Block::Air);

        void set_block(Block b, const glm::vec3& coords);
        Block get_block(const glm::vec3& coords) const;

        //Mesh build_simple_mesh() const;
        //Mesh build_greedy_mesh() const;

    private:
        std::size_t coords_to_array_index(const glm::vec3& coords) const;

        std::array<Block, CHUNK_SIZE> blocks;
    };
}
