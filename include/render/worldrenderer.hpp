#pragma once

#include <glm/glm.hpp>

#include <unordered_map>

#include "util/hash.hpp"
#include "util/camera.hpp"
#include "gfx/shader.hpp"
#include "gfx/mesh.hpp"
#include "world/chunk.hpp"

namespace render {
    class WorldRenderer {
    public:
        WorldRenderer(float face_size = 1.0f, bool greedy_meshing = false);
        void update(const util::Camera& camera);
        void draw() const;

        /// Generate and store  a chunk mesh VAO for the given chunk at the specified chunk coordinates (will overwrite
        /// existing VAO at those coordinates if any).
        void update_chunk_mesh(const glm::ivec3& coords, world::Chunk chunk);
        void remove_chunk_mesh(const glm::ivec3& coords);

    private:
        const float face_size;
        const bool greedy_meshing;

        gfx::ShaderProgram program;
        /// Map between chunk coordinates and their respective mesh.
        std::unordered_map<glm::ivec3, gfx::Mesh> chunk_meshes;
    };
}