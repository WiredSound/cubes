#pragma once

#include <glm/glm.hpp>

#include <vector>
#include <unordered_map>

#include "util/vertexcolour.hpp"
#include "gfx/mesh.hpp"
#include "world/chunk.hpp"

namespace world {
    class ChunkMeshBuilder {
    public:
        ChunkMeshBuilder(float face_size);
        gfx::Mesh build();

    protected:
        void build_face(glm::uvec3 bottom_left_pos, glm::uvec3 top_right_pos, const glm::vec3& colour);

    private:
        /// Will either create a new vertex with the specified colour and return its index, or will provide the index
        /// of an exist vertex should one already exist at the specified coordinates and with the specified colour.
        unsigned int require_vertex(const glm::vec3& coords, const glm::vec3& colour);

        const float face_size;

        unsigned int vertex_count = 0;
        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        std::unordered_map<util::VertexColour, unsigned int> past_vertex_colour_to_index;

    protected:
        const glm::vec3 top_face_colour_mod, bottom_face_colour_mod,
                        left_face_colour_mod, right_face_colour_mod,
                        front_face_colour_mod, back_face_colour_mod;
    };

    class SimpleChunkMeshBuilder : public ChunkMeshBuilder {
    public:
        SimpleChunkMeshBuilder(const Chunk& chunk, float face_size);

    private:
        void try_build_faces_around(const glm::uvec3& pos, const Chunk& chunk);
    };
}
