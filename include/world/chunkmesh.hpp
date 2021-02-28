#pragma once

#include <glm/glm.hpp>

#include <vector>
#include <unordered_map>

#include "util/mesh.hpp"
#include "world/chunk.hpp"

namespace world {
    class ChunkMeshBuilder {
    public:
        ChunkMeshBuilder(float face_size);
        util::Mesh build();

    protected:
        void build_face(const glm::uvec3& from_position, const glm::uvec3& to_position, const glm::vec3& colour);

    private:
        /// Will either create a new vertex with the specified colour and return its index, or will provide the index
        /// of an exist vertex should one already exist at the specified coordinates and with the specified colour.
        unsigned int require_vertex(const glm::vec3& coords, const glm::vec3& colour);

        const float face_size;

        unsigned int vertex_count = 0;
        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        struct VertexAndColour {
            glm::vec3 vertex;
            glm::vec3 colour;
        };

        // TODO: Create hashing function for above struct.
        //std::unordered_map<VertexColour, unsigned int> past_vertex_and_colour_to_index;
    };

    class SimpleChunkMeshBuilder : public ChunkMeshBuilder {
    public:
        SimpleChunkMeshBuilder(const Chunk& chunk, float face_size);

    private:
        void try_build_faces_around(const glm::uvec3& pos, const Chunk& chunk);
    };
}
