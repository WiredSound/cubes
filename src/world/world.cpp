#include <unordered_set>

#include "util/log.hpp"
#include "util/coords.hpp"
#include "world/world.hpp"

namespace world {
    optional_chunk_ref World::get_chunk(const glm::ivec3& coords) const {
        auto search = loaded_chunks.find(coords);

        if(search == loaded_chunks.end()) return {};
        else return std::make_optional(std::cref(search->second));
    }

    void World::camera_moved(const glm::vec3& pos, render::Renderer& renderer, text::DebugText& debug_text) {
        auto chunk_pos = world_position_to_chunk_position(pos);

        if(current_camera_chunk_pos != chunk_pos) {
            current_camera_chunk_pos = chunk_pos;
            handle_chunk_loading_unloading(renderer, debug_text);
        }
    }

    void World::set_in_memory_chunk_radius(unsigned int radius, render::Renderer& renderer, text::DebugText& debug_text) {
        if(in_memory_chunk_radius != radius) {
            in_memory_chunk_radius = radius;
            handle_chunk_loading_unloading(renderer, debug_text);
        }
    }

    void World::handle_chunk_loading_unloading(render::Renderer& renderer, text::DebugText& debug_text) {
        // TODO: Have chunks be loaded in a sphere around the camera rather than a cube.

        std::unordered_set<glm::ivec3> chunk_coords_to_be_loaded;

        auto radius = static_cast<int>(in_memory_chunk_radius);
        for(int x = current_camera_chunk_pos.x - radius; x < current_camera_chunk_pos.x + radius; x++) {
            for(int y = current_camera_chunk_pos.y - radius; y < current_camera_chunk_pos.y + radius; y++) {
                for(int z = current_camera_chunk_pos.z - radius; z < current_camera_chunk_pos.z + radius; z++) {
                    chunk_coords_to_be_loaded.insert(glm::ivec3(x, y, z));
                }
            }
        }

        // Unload all currently loaded chunks at coordinates that are not in the set of coordinates to be kept loaded:

        auto pair = loaded_chunks.begin();
        while(pair != loaded_chunks.end()) {
            auto search = chunk_coords_to_be_loaded.find(pair->first);

            if(search == chunk_coords_to_be_loaded.end()) {
                LOG("Chunk unloaded at chunk coords " << util::coords_to_string(pair->first));

                // TODO

                chunk_coords_to_be_loaded.erase(search);
                pair = loaded_chunks.erase(pair);
            }
            else pair++;
        }

        // Generate as necessary any chunks that are not currently loaded but should be:

        std::unordered_map<glm::ivec3, Chunk> new_chunks;
        // Mapping of chunk x and z coordinates to heightmaps generated from a noise function:
        std::unordered_map<glm::ivec2, std::vector<float>> noise_heightmaps;

        for(auto chunk_coords : chunk_coords_to_be_loaded) {
            const glm::ivec3 world_coords_chunk_corner = chunk_position_to_world_position(chunk_coords);

            const glm::ivec2 chunk_coords_xz(chunk_coords.x, chunk_coords.z);

            // If the necessary heightmap data isn't already present, generate it:

            if(noise_heightmaps.find(chunk_coords_xz) == noise_heightmaps.end()) {
                std::vector<float> noise_data(CHUNK_LENGTH * CHUNK_LENGTH);

                noise_fn->GenUniformGrid2D(
                    noise_data.data(),
                    world_coords_chunk_corner.x, world_coords_chunk_corner.z,
                    CHUNK_LENGTH, CHUNK_LENGTH,
                    0.2, noise_seed
                );

                noise_heightmaps.emplace(chunk_coords_xz, std::move(noise_data));
            }

            const auto& my_heightmap = noise_heightmaps.find(chunk_coords_xz)->second;

            // Create chunk and fill with blocks based on heightmap data:

            Chunk new_chunk(Block::None);

            for(int x_offset = 0; x_offset < static_cast<int>(CHUNK_LENGTH); x_offset++) {
                for(int z_offset = 0; z_offset < static_cast<int>(CHUNK_LENGTH); z_offset++) {
                    auto index = (z_offset * static_cast<int>(CHUNK_LENGTH)) + x_offset;
                    int sample_height = static_cast<int>(my_heightmap[index]) + 10;

                    for(int y_offset = 0; y_offset < static_cast<int>(CHUNK_LENGTH); y_offset++) {
                        glm::ivec3 world_coords = world_coords_chunk_corner + glm::ivec3(x_offset, y_offset, z_offset);

                        if(world_coords.y <= sample_height) {
                            glm::uvec3 offset_coords; // TODO
                            new_chunk.set_block(Block::Grass, offset_coords);
                        }
                    }
                }
            }

            LOG("New chunk generated at chunk coords " << util::coords_to_string(chunk_coords));

            new_chunks.emplace(chunk_coords, std::move(new_chunk));
        }

        // Add those new chunks to the world's loaded chunks:

        provide_chunks(std::move(new_chunks), renderer, debug_text);
    }

    void World::provide_chunk(glm::ivec3 coords, Chunk chunk, render::Renderer& renderer, text::DebugText& debug_text) {
        store_chunk(coords, std::move(chunk));

        // Update the chunk mesh and the meshes of any present adjacent chunks:
        update_chunk_mesh(coords, renderer.world_renderer);
        update_adjacent_chunk_meshes(coords, renderer.world_renderer);

        update_debug_text(renderer, debug_text);
    }

    void World::provide_chunks(std::unordered_map<glm::ivec3, Chunk> coords_chunks, render::Renderer& renderer, text::DebugText& debug_text) {
        for(auto& coords_chunk : coords_chunks) {
            store_chunk(coords_chunk.first, std::move(coords_chunk.second));
        }

        // Update chunk meshes:
        for(auto& coords_chunk : coords_chunks) {
            auto& coords = coords_chunk.first;

            update_chunk_mesh(coords, renderer.world_renderer);

            update_adjacent_chunk_meshes(
                coords, renderer.world_renderer,
                coords_chunks.find(util::coords_above(coords)) == coords_chunks.end(), // should update above chunk?
                coords_chunks.find(util::coords_below(coords)) == coords_chunks.end(), // should update chunk below?
                coords_chunks.find(util::coords_left(coords)) == coords_chunks.end(), // should update left chunk?
                coords_chunks.find(util::coords_right(coords)) == coords_chunks.end(), // should update right chunk?
                coords_chunks.find(util::coords_front(coords)) == coords_chunks.end(), // should update front chunk?
                coords_chunks.find(util::coords_rear(coords)) == coords_chunks.end() // should update rear chunk?
            );
        }

        update_debug_text(renderer, debug_text);
    }

    void World::remove_chunk(const glm::ivec3& coords, render::Renderer& renderer, text::DebugText& debug_text) {
        loaded_chunks.erase(coords);

        // Update chunk meshes:
        renderer.world_renderer.remove_chunk_mesh(coords);
        update_adjacent_chunk_meshes(coords, renderer.world_renderer);

        update_debug_text(renderer, debug_text);
    }

    void World::store_chunk(glm::ivec3 coords, Chunk chunk) {
        loaded_chunks.erase(coords);
        loaded_chunks.emplace(coords, std::move(chunk));

        LOG("Added chunk at " << util::coords_to_string(coords) << " to game world (now " << loaded_chunks.size() + 1
            << " loaded chunks)");
    }

    void World::update_chunk_mesh(glm::ivec3 coords, render::WorldRenderer& world_renderer) const {
        auto chunk = get_chunk(coords);

        if(chunk) {
            world_renderer.update_chunk_mesh(
                coords, *chunk,
                get_chunk(util::coords_above(coords)), get_chunk(util::coords_below(coords)),
                get_chunk(util::coords_left(coords)), get_chunk(util::coords_right(coords)),
                get_chunk(util::coords_front(coords)), get_chunk(util::coords_rear(coords))
            );
        }
    }

    void World::update_adjacent_chunk_meshes(
        const glm::ivec3& coords, render::WorldRenderer& world_renderer,
        bool update_chunk_above, bool update_chunk_below,
        bool update_chunk_left, bool update_chunk_right,
        bool update_chunk_front, bool update_chunk_rear
    ) const {
        if(update_chunk_above) update_chunk_mesh(util::coords_above(coords), world_renderer);
        if(update_chunk_below) update_chunk_mesh(util::coords_below(coords), world_renderer);
        if(update_chunk_left) update_chunk_mesh(util::coords_left(coords), world_renderer);
        if(update_chunk_right) update_chunk_mesh(util::coords_right(coords), world_renderer);
        if(update_chunk_front) update_chunk_mesh(util::coords_front(coords), world_renderer);
        if(update_chunk_rear) update_chunk_mesh(util::coords_rear(coords), world_renderer);
    }

    void World::update_debug_text(render::Renderer& renderer, text::DebugText& debug_text) const {
        debug_text.update_chunks_loaded(loaded_chunks.size(), renderer.debug_text_renderer);
        // TODO: Display in-memory chunk radius & number of loaded chunks.
    }
}
