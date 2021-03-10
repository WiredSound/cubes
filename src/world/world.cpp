#include "world/world.hpp"

namespace world {
    bool World::is_chunk_loaded_at(const glm::ivec3& coords) const {
        return loaded_chunks.find(coords) != loaded_chunks.end();
    }

    void World::provide_chunk(const glm::ivec3& coords, Chunk chunk, render::WorldRenderer& renderer) {
        auto chunk_above = get_chunk(coords + glm::ivec3(0, 1, 0)),
             chunk_below = get_chunk(coords - glm::ivec3(0, 1, 0)),
             chunk_left = get_chunk(coords - glm::ivec3(1, 0, 0)),
             chunk_right = get_chunk(coords + glm::ivec3(1, 0, 0)),
             chunk_front = get_chunk(coords - glm::ivec3(0, 0, 1)),
             chunk_rear = get_chunk(coords + glm::ivec3(0, 0, 1));

        // Update the chunk mesh:
        renderer.update_chunk_mesh(
            coords, chunk,
            chunk_above, chunk_below,
            chunk_left, chunk_right,
            chunk_front, chunk_rear
        );

        // TODO: Update meshes of any adjacent chunks that are present.

        // Store the chunk:
        loaded_chunks[coords] = std::move(chunk);
    }

    void World::remove_chunk(const glm::ivec3& coords, render::WorldRenderer& renderer) {
        loaded_chunks.erase(coords);
        renderer.remove_chunk_mesh(coords);
    }

    optional_chunk_ref World::get_chunk(const glm::ivec3& coords) {
        auto search = loaded_chunks.find(coords);

        if(search == loaded_chunks.end()) return {};
        else return std::make_optional(std::ref(search->second));
    }
}
