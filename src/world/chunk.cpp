#include "world/chunk.hpp"

namespace world {
    Chunk::Chunk() : blocks{ Block::None } {}

    void Chunk::set_block(Block b, const glm::vec3& coords) {
        blocks[coords_to_array_index(coords)] = b;
    }

    Block Chunk::get_block(const glm::vec3& coords) const {
        return blocks[coords_to_array_index(coords)];
    }

    //Mesh Chunk::build_simple_mesh() const {}

    //Mesh Chunk::build_greedy_mesh() const {}

    std::size_t Chunk::coords_to_array_index(const glm::vec3& coords) const {
        return (CHUNK_LENGTH * coords.z + coords.y) * CHUNK_LENGTH + coords.x;
    }
}
