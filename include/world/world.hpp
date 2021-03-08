#pragma once

#include <unordered_map>

#include "util/hash.hpp"
#include "render/worldrenderer.hpp"

namespace world {
    class World {
    public:
        bool is_chunk_loaded_at(const glm::ivec3& coords) const;
        void provide_chunk(const glm::ivec3& coords, Chunk chunk, render::WorldRenderer& renderer);
        void remove_chunk(const glm::ivec3& coords, render::WorldRenderer& renderer);

    private:
        // Map between chunk coordinates and chunks.
        std::unordered_map<glm::ivec3, Chunk> loaded_chunks;
    };
}
