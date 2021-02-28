#include <glm/glm.hpp>

#include <utility>

#include "world/chunkmesh.hpp"

namespace world {
    ChunkMeshBuilder::ChunkMeshBuilder(float face_size) : face_size(face_size) {}

    util::Mesh ChunkMeshBuilder::build() {
        return util::Mesh { std::move(vertices), std::move(indices) };
    }

    void ChunkMeshBuilder::build_face(const glm::uvec3& from_position, const glm::uvec3& to_position, const glm::vec3& colour) {
        // ...
    }

    unsigned int ChunkMeshBuilder::require_vertex(const glm::vec3& coords, const glm::vec3& colour) {
        auto search = past_vertex_and_colour_to_index.find(VertexAndColour { coords, colour });

        if(search != past_vertex_and_colour_to_index.end()) { // Return index of existing vertex:
            return search->second;
        }
        else { // Create new vertex and then return its index:
            float new_vertices[] = {
                coords.x, coords.y, coords.z,
                colour.x, colour.y, colour.z
            };
            vertices.insert(vertices.end(), new_vertices, new_vertices + 6);

            vertex_count++;

            return vertex_count - 1;
        }
    }
    
    SimpleChunkMeshBuilder::SimpleChunkMeshBuilder(const Chunk& chunk, float face_size) : ChunkMeshBuilder(face_size) {
        glm::uvec3 pos;

        for(pos.x = 0; pos.x < CHUNK_LENGTH; pos.x++) {
            for(pos.y = 0; pos.y < CHUNK_LENGTH; pos.y++) {
                for(pos.z = 0; pos.z < CHUNK_LENGTH; pos.z++) {
                    try_build_faces_around(pos, chunk);
                }
            }
        }
    }

    void SimpleChunkMeshBuilder::try_build_faces_around(const glm::uvec3& pos, const Chunk& chunk) {
        /*if(chunk.get_block(x, y, z) != Block::None) {
            // Left face:
            if(x > 0 && chunk.get_block(x - 1, y, z) == Block::None)
                build_block_face(x, y, z, x, y + 1, z + 1);
            // Right face:
            if(x < CHUNK_LENGTH - 1 && chunk.get_block(x + 1, y, z) == Block::None)
                build_block_face(x + 1, z, y, x + 1, y + 1, z + 1);
            // Bottom face:
            if(y > 0 && chunk.get_block(x, y - 1, z) == Block::None)
                build_block_face(x, y, z, x + 1, y, z + 1);
            // Top face:
            if(y < CHUNK_LENGTH - 1 && chunk.get_block(x, y + 1, z) == Block::None)
                build_block_face(x, y + 1, z, x + 1, y + 1, z + 1);
            // Front face:
            if(z > 0 && chunk.get_block(x, y, z - 1) == Block::None)
                build_block_face(x, y, z, x + 1, y + 1, z);
            // Rear face:
            if(z < CHUNK_LENGTH - 1 && chunk.get_block(x, y, z + 1) == Block::None)
                build_block_face(x, y, z + 1, x + 1, y + 1, z + 1);
        }*/
    }
}
