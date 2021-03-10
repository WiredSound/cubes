#pragma once

#include <glm/glm.hpp>

#include <array>
#include <vector>
#include <cstddef>
#include <optional>
#include <functional>

#include "gfx/mesh.hpp"
#include "world/block.hpp"

namespace world {
    /// Width, depth, height of a single chunk.
    constexpr unsigned int CHUNK_LENGTH = 16;
    /// Number of blocks per chunk.
    constexpr unsigned int CHUNK_SIZE = CHUNK_LENGTH * CHUNK_LENGTH * CHUNK_LENGTH;

    class Chunk;
    using optional_chunk_ref = std::optional<std::reference_wrapper<const Chunk>>;

    class Chunk {
    public:
        Chunk(Block fill_block = Block::None);

        void set_block(Block b, const glm::uvec3& pos);
        Block get_block(const glm::uvec3& pos) const;
        bool is_no_block_at(const glm::uvec3& pos) const;

        gfx::Mesh build_simple_mesh(
            float face_size,
            optional_chunk_ref above_chunk, optional_chunk_ref below_chunk,
            optional_chunk_ref left_chunk, optional_chunk_ref right_chunk,
            optional_chunk_ref front_chunk, optional_chunk_ref rear_chunk
        ) const;

        //gfx::Mesh build_greedy_mesh(float face_size) const;

    private:
        std::size_t pos_to_array_index(const glm::uvec3& pos) const;

        std::array<Block, CHUNK_SIZE> blocks;
    };
}
