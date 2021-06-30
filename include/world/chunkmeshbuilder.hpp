#pragma once

#include <glm/glm.hpp>

#include <vector>
#include <unordered_map>

#include "world/chunk.hpp"
#include "world/chunkmesh.hpp"
#include "util/vertex.hpp"
#include "util/meshbuilder.hpp"

namespace world {
    class ChunkMeshBuilder : public util::MeshBuilder<util::Position3Colour3, ChunkMesh, 6> {
    public:
        ChunkMeshBuilder(float face_size);

    protected:
        std::string vertex_to_string(const util::Position3Colour3& vertex) override;

        std::array<float, 6> vertex_to_data(const util::Position3Colour3& vertex) override;

        void build_face(glm::uvec3 bottom_left_pos, glm::uvec3 top_right_pos, const glm::vec3& colour);
        
    protected:
        const glm::vec3 top_face_colour_mod, bottom_face_colour_mod,
                        left_face_colour_mod, right_face_colour_mod,
                        front_face_colour_mod, back_face_colour_mod;
    
    private:
        const float face_size;
    };

    class SimpleChunkMeshBuilder : public ChunkMeshBuilder {
    public:
        SimpleChunkMeshBuilder(
            float face_size, const Chunk& chunk,
            optional_chunk_ref above_chunk, optional_chunk_ref below_chunk,
            optional_chunk_ref left_chunk, optional_chunk_ref right_chunk,
            optional_chunk_ref front_chunk, optional_chunk_ref rear_chunk
        );

    private:
        void try_build_faces_around(
            const glm::uvec3& pos, const Chunk& chunk,
            optional_chunk_ref above_chunk, optional_chunk_ref below_chunk,
            optional_chunk_ref left_chunk, optional_chunk_ref right_chunk,
            optional_chunk_ref front_chunk, optional_chunk_ref rear_chunk
        );
    };
}
