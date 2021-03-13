#pragma once

#include <glm/glm.hpp>

#include <unordered_map>

#include "util/hash.hpp"
#include "util/camera.hpp"
#include "gfx/shader.hpp"
#include "world/chunk.hpp"
#include "world/chunkmesh.hpp"

// Forward-declaration so `WorldRenderer` can be a friend of `world::World`.
namespace world { class World; }

namespace render {
    class WorldRenderer {
    public:
        WorldRenderer(float face_size = 1.0f, bool greedy_meshing = false);
        void update(const util::Camera& camera);
        void draw() const;

    private:
        // `world::World` is a friend so that only that class can update/remove chunk meshes.
        friend world::World;

        /// Generate and store  a chunk mesh VAO for the given chunk at the specified chunk coordinates (will overwrite
        /// existing VAO at those coordinates if any). This method is to be called by `world::World` whenever one of its
        /// chunks are modified or a new chunk is added.
        void update_chunk_mesh(
            const glm::ivec3& coords, const world::Chunk& chunk,
            world::optional_chunk_ref above_chunk, world::optional_chunk_ref below_chunk,
            world::optional_chunk_ref left_chunk, world::optional_chunk_ref right_chunk,
            world::optional_chunk_ref front_chunk, world::optional_chunk_ref rear_chunk
        );

        /// Removes the mesh for the chunk at the specified coordinates. This method is to be called by `world::World`
        /// whenever one of its chunks is unloaded/removed.
        void remove_chunk_mesh(const glm::ivec3& coords);

        const float face_size;
        const bool greedy_meshing;

        gfx::ShaderProgram program;

        /// Map between chunk coordinates and their respective mesh.
        std::unordered_map<glm::ivec3, world::ChunkMesh> chunk_meshes;
    };
}
