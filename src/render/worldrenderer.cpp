#include "render/worldrenderer.hpp"
#include "util/log.hpp"

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

        // Update world vertex array...
    }

    void WorldRenderer::draw() const {
        program.use();

        for(auto& iter : chunk_meshes) {
            auto& mesh = iter.second;

            // TODO: Set model uniform based on chunk coordinates.

            mesh.bind_and_draw();
        }
    }
        
    void WorldRenderer::update_chunk_mesh(const glm::ivec3& coords, const world::Chunk& chunk) {
        LOG("Generating mesh for chunk at " << util::vec3_to_string(coords));
        if(greedy_meshing) {
            // ...
        }
        else { // simple meshing
            auto mesh = chunk.build_simple_mesh(face_size);
            chunk_meshes.emplace(coords, std::move(mesh));
        }
    }

    void WorldRenderer::remove_chunk_mesh(const glm::ivec3& coords) {
        chunk_meshes.erase(coords);
    }
}
