#include "world/world.hpp"

namespace world {
    bool World::is_chunk_loaded_at(const glm::ivec3& coords) const {
        return loaded_chunks.find(coords) != loaded_chunks.end();
    }

    void World::provide_chunk(const glm::ivec3& coords, Chunk chunk, render::WorldRenderer& renderer) {
        loaded_chunks[coords] = std::move(chunk);
        renderer.update_chunk_mesh(coords, loaded_chunks.find(coords)->second);
    }

    void World::remove_chunk(const glm::ivec3& coords, render::WorldRenderer& renderer) {
        loaded_chunks.erase(coords);
        renderer.remove_chunk_mesh(coords);
    }
}
