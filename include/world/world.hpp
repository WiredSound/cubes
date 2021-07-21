#pragma once

#include <FastNoise/FastNoise.h>

#include <unordered_map>

#include "util/hash.hpp"
#include "world/chunk.hpp"
#include "text/debugtext.hpp"
#include "render/renderer.hpp"

namespace world {
    class World {
    public:
        /// Get a constant reference to the chunk at the given chunk coordinates.
        optional_chunk_ref get_chunk(const glm::ivec3& coords) const;

        /// Ensure chunks within the in-memory chunk radius relative to the camera's position are loaded and chunks
        /// outside of that area are not loaded.
        void camera_moved(const glm::vec3& pos, render::Renderer& renderer, text::DebugText& debug_text);

        /// Update the radius of chunks which will be kept loaded.
        void set_in_memory_chunk_radius(unsigned int radius, render::Renderer& renderer, text::DebugText& debug_text);

    private:
        /// Based on the current position of the camera and radius of chunks being kept in memory and rendered, this
        /// method ensures that only the correct chunks are loaded. Currently, chunks are always newly generated rather
        /// than being loaded from disk or otherwise.
        void handle_chunk_loading_unloading(render::Renderer& renderer, text::DebugText& debug_text);

        /// Store a single chunk in this world at the specified chunk coordinates. A mesh will be generated for the new
        /// chunk and stored in the provided world renderer. Note that if any chunks are adjacent to the provided chunk,
        /// their meshes will be updated also.
        void provide_chunk(glm::ivec3 coords, Chunk chunk, render::Renderer& renderer, text::DebugText& debug_text);

        /// Store multiple chunks in this world. This method should be prefered to sequentially calling `provide_chunk`
        /// for a group of adjacent chunks as it prevents repeatedly rebuilding chunk meshes unnecessarily.
        void provide_chunks(std::unordered_map<glm::ivec3, Chunk> coords_chunks, render::Renderer& renderer, text::DebugText& debug_text);

        void remove_chunk(const glm::ivec3& coords, render::Renderer& renderer, text::DebugText& debug_text);

        /// Add a chunk at the specified coordinates to the game world without performing any updates to rendering state
        /// or meshes.
        void store_chunk(glm::ivec3 coords, Chunk chunk);

        void update_chunk_mesh(glm::ivec3 coords, render::WorldRenderer& world_renderer) const;

        void update_adjacent_chunk_meshes(
            const glm::ivec3& coords, render::WorldRenderer& world_renderer,
            bool update_chunk_above = true, bool update_chunk_below = true,
            bool update_chunk_left = true, bool update_chunk_right = true,
            bool update_chunk_front = true, bool update_chunk_rear = true
        ) const;

        void update_debug_text(render::Renderer& renderer, text::DebugText& debug_text) const;

        /// Chunks within a sphere of this radius around the position of the camera will be loaded (with render meshes)
        /// while those outside will not.
        unsigned int in_memory_chunk_radius = 2;

        /// Current position of the camera in chunk coordinates.
        glm::ivec3 current_camera_chunk_pos;

        /// Map between chunk coordinates and chunks.
        std::unordered_map<glm::ivec3, Chunk> loaded_chunks;

        int noise_seed = 12345;
        FastNoise::SmartNode<FastNoise::Simplex> noise_fn = FastNoise::New<FastNoise::Simplex>();
    };
}
