#include <cassert>
#include <utility>

#include "world/chunkmesh.hpp"

namespace world {
    ChunkMeshBuilder::ChunkMeshBuilder(float face_size)
        : face_size(face_size), top_face_colour_mod(0.025f), bottom_face_colour_mod(-0.05),
          left_face_colour_mod(-0.025), right_face_colour_mod(0.0f),
          front_face_colour_mod(0.0f), back_face_colour_mod(-0.025) {}

    gfx::Mesh ChunkMeshBuilder::build() {
        return gfx::Mesh(vertices, indices, vertex_count);
    }

    void ChunkMeshBuilder::build_face(glm::uvec3 bottom_left_pos, glm::uvec3 top_right_pos, const glm::vec3& colour) {
        // TODO: Only run these assertions if debug or test build.
        assert(top_right_pos.x >= bottom_left_pos.x);
        assert(top_right_pos.y >= bottom_left_pos.y);
        assert(top_right_pos.z >= bottom_left_pos.z);

        auto bottom_left_coords = static_cast<glm::vec3>(bottom_left_pos) * face_size;
        auto top_right_coords = static_cast<glm::vec3>(top_right_pos) * face_size;

        glm::vec3 bottom_right_coords, top_left_coords;

        if(bottom_left_pos.z == top_right_pos.z) { // front or rear face
            bottom_right_coords = bottom_left_coords + glm::vec3(face_size, 0.0f, 0.0f);
            top_left_coords = top_right_coords - glm::vec3(face_size, 0.0f, 0.0f);
        }
        else if(bottom_left_pos.y == top_right_pos.y) { // top or bottom face
            bottom_right_coords = bottom_left_coords + glm::vec3(face_size, 0.0f, 0.0f);
            top_left_coords = top_right_coords - glm::vec3(face_size, 0.0f, 0.0f);
        }
        else if(bottom_left_pos.x == top_right_pos.x) { // left or right face
            bottom_right_coords = bottom_left_coords + glm::vec3(0.0f, 0.0f, face_size);
            top_left_coords = top_right_coords - glm::vec3(0.0f, 0.0f, face_size);
        }

        unsigned int bottom_left = require_vertex(bottom_left_coords, colour),
                     bottom_right = require_vertex(bottom_right_coords, colour),
                     top_left = require_vertex(top_left_coords, colour),
                     top_right = require_vertex(top_right_coords, colour);

        unsigned int new_indices[] = {
            top_right, bottom_right, top_left,
            bottom_right, bottom_left, top_left
        };
        indices.insert(indices.end(), new_indices, new_indices + 6);
    }

    unsigned int ChunkMeshBuilder::require_vertex(const glm::vec3& coords, const glm::vec3& colour) {
        auto search = past_vertex_colour_to_index.find(util::VertexColour { coords, colour });

        if(search != past_vertex_colour_to_index.end()) { // Return index of existing vertex:
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
        Block block = chunk.get_block(pos);
        glm::vec3 colour = get_block_colour(block);

        if(block != Block::None) {
            // Left face:
            if(pos.x > 0 && chunk.get_block(pos - glm::uvec3(1, 0, 0)) == Block::None)
                build_face(pos, pos + glm::uvec3(0, 1, 1), colour + left_face_colour_mod);
            // Right face:
            if(pos.x < CHUNK_LENGTH - 1 && chunk.get_block(pos + glm::uvec3(1, 0, 0)) == Block::None)
                build_face(pos + glm::uvec3(1, 0, 0), pos + 1u, colour + right_face_colour_mod);
            // Bottom face:
            if(pos.y > 0 && chunk.get_block(pos - glm::uvec3(0, 1, 0)) == Block::None)
                build_face(pos, pos + glm::uvec3(1, 0, 1), colour + bottom_face_colour_mod);
            // Top face:
            if(pos.y < CHUNK_LENGTH - 1 && chunk.get_block(pos + glm::uvec3(0, 1, 0)) == Block::None)
                build_face(pos + glm::uvec3(0, 1, 0), pos + 1u, colour + top_face_colour_mod);
            // Front face:
            if(pos.z > 0 && chunk.get_block(pos - glm::uvec3(0, 0, 1)) == Block::None)
                build_face(pos, pos + glm::uvec3(1, 1, 0), colour + front_face_colour_mod);
            // Rear face:
            if(pos.z < CHUNK_LENGTH - 1 && chunk.get_block(pos + glm::uvec3(0, 0, 1)) == Block::None)
                build_face(pos + glm::uvec3(0, 0, 1), pos + 1u, colour + back_face_colour_mod);
        }
    }
}
