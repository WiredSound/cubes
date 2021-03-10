#include <glm/gtx/transform.hpp>

#include "util/log.hpp"
#include "render/worldrenderer.hpp"

namespace render {
    WorldRenderer::WorldRenderer(float face_size, bool greedy_meshing) : face_size(face_size), greedy_meshing(greedy_meshing) {
        gfx::Shader vertex("shaders/world.vert", gfx::ShaderType::Vertex);
        program.attach(vertex);

        gfx::Shader fragment("shaders/world.frag", gfx::ShaderType::Fragment);
        program.attach(fragment);

        program.link();
    }

    void WorldRenderer::update(const util::Camera& camera) {
        program.use();
        program.set_uniform("projection", camera.get_projection_matrix());
        program.set_uniform("view", camera.get_view_matrix());
    }

    void WorldRenderer::draw() const {
        program.use();

        for(auto& iter : chunk_meshes) {
            auto chunk_coords = iter.first;
            auto& mesh = iter.second;

            auto model_offset = static_cast<glm::vec3>(chunk_coords * static_cast<int>(world::CHUNK_LENGTH)) * face_size;
            glm::mat4 model_matrix = glm::translate(glm::mat4(1.0f), model_offset);
            program.set_uniform("model", model_matrix);

            mesh.bind_and_draw();
        }
    }
        
    void WorldRenderer::update_chunk_mesh(
        const glm::ivec3& coords, const world::Chunk& chunk,
        world::optional_chunk_ref above_chunk, world::optional_chunk_ref below_chunk,
        world::optional_chunk_ref left_chunk, world::optional_chunk_ref right_chunk,
        world::optional_chunk_ref front_chunk, world::optional_chunk_ref rear_chunk
    ) {
        LOG("Generating mesh for chunk at " << util::vec3_to_string(coords));

        if(greedy_meshing) {
            // ...
        }
        else { // simple meshing
            auto mesh = chunk.build_simple_mesh(
                face_size,
                above_chunk, below_chunk,
                left_chunk, right_chunk,
                front_chunk, rear_chunk
            );

            chunk_meshes.erase(coords);
            chunk_meshes.emplace(coords, std::move(mesh));
        }
    }

    void WorldRenderer::remove_chunk_mesh(const glm::ivec3& coords) {
        chunk_meshes.erase(coords);
    }
}
