#include "util/log.hpp"
#include "util/coords.hpp"
#include "world/world.hpp"

namespace world {
    optional_chunk_ref World::get_chunk(const glm::ivec3& coords) {
        auto search = loaded_chunks.find(coords);

        if(search == loaded_chunks.end()) return {};
        else return std::make_optional(std::ref(search->second));
    }

    void World::provide_chunk(glm::ivec3 coords, Chunk chunk, render::WorldRenderer& renderer) {
        store_chunk(coords, std::move(chunk));

        // Update the chunk mesh and the meshes of any present adjacent chunks:

        update_chunk_mesh(coords, renderer);
        update_adjacent_chunk_meshes(coords, renderer);
    }

    void World::provide_chunks(std::unordered_map<glm::ivec3, Chunk> coords_chunks, render::WorldRenderer& renderer) {
        for(auto& coords_chunk : coords_chunks) {
            store_chunk(coords_chunk.first, std::move(coords_chunk.second));
        }

        // Update chunk meshes:
        for(auto& coords_chunk : coords_chunks) {
            auto& coords = coords_chunk.first;

            update_chunk_mesh(coords, renderer);

            update_adjacent_chunk_meshes(
                coords, renderer,
                coords_chunks.find(util::coords_above(coords)) == coords_chunks.end(), // should update above chunk?
                coords_chunks.find(util::coords_below(coords)) == coords_chunks.end(), // should update chunk below?
                coords_chunks.find(util::coords_left(coords)) == coords_chunks.end(), // should update left chunk?
                coords_chunks.find(util::coords_right(coords)) == coords_chunks.end(), // should update right chunk?
                coords_chunks.find(util::coords_front(coords)) == coords_chunks.end(), // should update front chunk?
                coords_chunks.find(util::coords_rear(coords)) == coords_chunks.end() // should update rear chunk?
            );
        }
    }

    void World::remove_chunk(const glm::ivec3& coords, render::WorldRenderer& renderer) {
        loaded_chunks.erase(coords);

        renderer.remove_chunk_mesh(coords);
        update_adjacent_chunk_meshes(coords, renderer);
    }

    void World::store_chunk(glm::ivec3 coords, Chunk chunk) {
        loaded_chunks.erase(coords);
        loaded_chunks.emplace(coords, std::move(chunk));

        LOG("Added chunk at " << util::vec3_to_string(coords) << " to game world (now " << loaded_chunks.size() + 1
            << " loaded chunks)");
    }

    void World::update_chunk_mesh(glm::ivec3 coords, render::WorldRenderer& renderer) {
        auto chunk = get_chunk(coords);

        if(chunk) {
            renderer.update_chunk_mesh(
                coords, *chunk,
                get_chunk(util::coords_above(coords)), get_chunk(util::coords_below(coords)),
                get_chunk(util::coords_left(coords)), get_chunk(util::coords_right(coords)),
                get_chunk(util::coords_front(coords)), get_chunk(util::coords_rear(coords))
            );
        }
    }

    void World::update_adjacent_chunk_meshes(
        const glm::ivec3& coords, render::WorldRenderer& renderer,
        bool update_chunk_above, bool update_chunk_below,
        bool update_chunk_left, bool update_chunk_right,
        bool update_chunk_front, bool update_chunk_rear
    ) {
        if(update_chunk_above) update_chunk_mesh(util::coords_above(coords), renderer);
        if(update_chunk_below) update_chunk_mesh(util::coords_below(coords), renderer);
        if(update_chunk_left) update_chunk_mesh(util::coords_left(coords), renderer);
        if(update_chunk_right) update_chunk_mesh(util::coords_right(coords), renderer);
        if(update_chunk_front) update_chunk_mesh(util::coords_front(coords), renderer);
        if(update_chunk_rear) update_chunk_mesh(util::coords_rear(coords), renderer);
    }
}
