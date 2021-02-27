#pragma once

#include <unordered_map>

#include "chunk.hpp"

namespace world {
    class World {
    private:
        /// Map between chunk coordinates and chunks.
        //std::unordered_map<glm::vec3, Chunk> loaded_chunks;
        // TODO: Need a hashable key for unordered_map!
    };
}
