#pragma once

#include <unordered_map>

#include "util/hash.hpp"
#include "world/chunk.hpp"
#include "text/debugtext.hpp"
#include "render/renderer.hpp"

namespace world {
    class World {
    public:
        optional_chunk_ref get_chunk(const glm::ivec3& coords) const;

        /// Store a single chunk in this world at the specified chunk coordinates. A mesh will be generated for the new
        /// chunk and stored in the provided world renderer. Note that if any chunks are adjacent to the provided chunk,
        /// their meshes will be updated also.
        void provide_chunk(glm::ivec3 coords, Chunk chunk, render::Renderer& renderer, text::DebugText& debug_text);

        /// Store multiple chunks in this world. This method should be prefered to sequentially calling `provide_chunk`
        /// for a group of adjacent chunks as it prevents repeatedly rebuilding chunk meshes unnecessarily.
        void provide_chunks(std::unordered_map<glm::ivec3, Chunk> coords_chunks, render::Renderer& renderer, text::DebugText& debug_text);

        void remove_chunk(const glm::ivec3& coords, render::Renderer& renderer, text::DebugText& debug_text);

    private:
        void store_chunk(glm::ivec3 coords, Chunk chunk);

        void update_chunk_mesh(glm::ivec3 coords, render::WorldRenderer& world_renderer) const;

        void update_adjacent_chunk_meshes(
            const glm::ivec3& coords, render::WorldRenderer& world_renderer,
            bool update_chunk_above = true, bool update_chunk_below = true,
            bool update_chunk_left = true, bool update_chunk_right = true,
            bool update_chunk_front = true, bool update_chunk_rear = true
        ) const;

        void update_debug_text(render::Renderer& renderer, text::DebugText& debug_text) const;

        // Map between chunk coordinates and chunks.
        std::unordered_map<glm::ivec3, Chunk> loaded_chunks;
    };
}
