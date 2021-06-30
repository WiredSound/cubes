#include <utility>

#include "util/log.hpp"
#include "util/coords.hpp"
#include "util/assert.hpp"
#include "world/chunkmeshbuilder.hpp"

namespace world {
    ChunkMeshBuilder::ChunkMeshBuilder(float face_size)
        : top_face_colour_mod(0.025f), bottom_face_colour_mod(-0.05f),
          left_face_colour_mod(-0.025f), right_face_colour_mod(0.0f),
          front_face_colour_mod(0.0f), back_face_colour_mod(-0.025f),
          face_size(face_size) {}
    
    std::array<float, 6> ChunkMeshBuilder::vertex_to_data(const util::Position3Colour3& vertex) {
        return {
            vertex.position.x, vertex.position.y, vertex.position.z,
            vertex.colour.x, vertex.colour.y, vertex.colour.z
        };
    }

    void ChunkMeshBuilder::build_face(glm::uvec3 bottom_left_pos, glm::uvec3 top_right_pos, const glm::vec3& colour) {
        DEBUG_ASSERT(top_right_pos.x >= bottom_left_pos.x);
        DEBUG_ASSERT(top_right_pos.y >= bottom_left_pos.y);
        DEBUG_ASSERT(top_right_pos.z >= bottom_left_pos.z);

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

        unsigned int bottom_left = require_vertex(util::Position3Colour3 { bottom_left_coords, colour }),
                     bottom_right = require_vertex(util::Position3Colour3 { bottom_right_coords, colour }),
                     top_left = require_vertex(util::Position3Colour3 { top_left_coords, colour }),
                     top_right = require_vertex(util::Position3Colour3 { top_right_coords, colour });

        unsigned int new_indices[] = {
            top_right, bottom_right, top_left,
            bottom_right, bottom_left, top_left
        };
        indices.insert(indices.end(), new_indices, new_indices + 6);
    }

    SimpleChunkMeshBuilder::SimpleChunkMeshBuilder(
        float face_size, const Chunk& chunk,
        optional_chunk_ref above_chunk, optional_chunk_ref below_chunk,
        optional_chunk_ref left_chunk, optional_chunk_ref right_chunk,
        optional_chunk_ref front_chunk, optional_chunk_ref rear_chunk
    ) : ChunkMeshBuilder(face_size) {
        glm::uvec3 pos;

        for(pos.x = 0; pos.x < CHUNK_LENGTH; pos.x++) {
            for(pos.y = 0; pos.y < CHUNK_LENGTH; pos.y++) {
                for(pos.z = 0; pos.z < CHUNK_LENGTH; pos.z++) {
                    try_build_faces_around(
                        pos, chunk,
                        above_chunk, below_chunk,
                        left_chunk, right_chunk,
                        front_chunk, rear_chunk
                    );
                }
            }
        }
    }

    void SimpleChunkMeshBuilder::try_build_faces_around(
        const glm::uvec3& pos, const Chunk& chunk,
        optional_chunk_ref above_chunk, optional_chunk_ref below_chunk,
        optional_chunk_ref left_chunk, optional_chunk_ref right_chunk,
        optional_chunk_ref front_chunk, optional_chunk_ref rear_chunk
    ) {
        Block block = chunk.get_block(pos);
        glm::vec3 colour = get_block_colour(block);

        // TODO: Reduce repetition in the following code:

        if(block != Block::None) {
            // Left face:

            bool no_block_left_in_chunk = pos.x > 0 && chunk.is_no_block_at(pos - glm::uvec3(1, 0, 0));
            bool no_block_in_left_chunk =
                pos.x == 0 && (!left_chunk || left_chunk->get().is_no_block_at(pos + glm::uvec3(CHUNK_LENGTH - 1, 0, 0)));

            if(no_block_left_in_chunk || no_block_in_left_chunk) {
                build_face(pos, pos + glm::uvec3(0, 1, 1), colour + left_face_colour_mod);
            }

            // Right face:

            bool no_block_right_in_chunk = pos.x < CHUNK_LENGTH - 1 && chunk.is_no_block_at(pos + glm::uvec3(1, 0, 0));
            bool no_block_in_right_chunk =
                pos.x == CHUNK_LENGTH - 1 && (!right_chunk || right_chunk->get().is_no_block_at(pos - glm::uvec3(CHUNK_LENGTH - 1, 0, 0)));

            if(no_block_right_in_chunk || no_block_in_right_chunk) {
                build_face(pos + glm::uvec3(1, 0, 0), pos + 1u, colour + right_face_colour_mod);
            }

            // Bottom face:

            bool no_block_below_in_chunk = pos.y > 0 && chunk.is_no_block_at(pos - glm::uvec3(0, 1, 0));
            bool no_block_in_below_chunk =
                pos.y == 0 && (!below_chunk || below_chunk->get().is_no_block_at(pos + glm::uvec3(0, CHUNK_LENGTH, 0)));

            if(no_block_below_in_chunk || no_block_in_below_chunk) {
                build_face(pos, pos + glm::uvec3(1, 0, 1), colour + bottom_face_colour_mod);
            }

            // Top face:

            bool no_block_above_in_chunk = pos.y < CHUNK_LENGTH - 1 && chunk.is_no_block_at(pos + glm::uvec3(0, 1, 0));
            bool no_block_in_above_chunk =
                pos.y == CHUNK_LENGTH - 1 && (!above_chunk || above_chunk->get().is_no_block_at(pos - glm::uvec3(0, CHUNK_LENGTH - 1, 0)));

            if(no_block_above_in_chunk || no_block_in_above_chunk) {
                build_face(pos + glm::uvec3(0, 1, 0), pos + 1u, colour + top_face_colour_mod);
            }

            // Front face:

            bool no_block_front_in_chunk = pos.z > 0 && chunk.is_no_block_at(pos - glm::uvec3(0, 0, 1));
            bool no_block_in_front_chunk =
                pos.z == 0 && (!front_chunk || front_chunk->get().is_no_block_at(pos + glm::uvec3(0, 0, CHUNK_LENGTH - 1)));

            if(no_block_front_in_chunk || no_block_in_front_chunk) {
                build_face(pos, pos + glm::uvec3(1, 1, 0), colour + front_face_colour_mod);
            }

            // Rear face:

            bool no_block_rear_in_chunk = pos.z < CHUNK_LENGTH - 1 && chunk.get_block(pos + glm::uvec3(0, 0, 1)) == Block::None;
            bool no_block_in_rear_chunk =
                pos.z == CHUNK_LENGTH - 1 && (!rear_chunk || rear_chunk->get().is_no_block_at(pos - glm::uvec3(0, 0, CHUNK_LENGTH - 1)));

            if(no_block_rear_in_chunk || no_block_in_rear_chunk) {
                build_face(pos + glm::uvec3(0, 0, 1), pos + 1u, colour + back_face_colour_mod);
            }
        }
    }
}
