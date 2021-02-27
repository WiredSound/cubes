#include "render/worldrenderer.hpp"

namespace render {
    WorldRenderer::WorldRenderer() {
        Shader vertex("shaders/world.vert");
        program.attach(vertex, gfx::ShaderType::Vertex);

        Shader fragment("shaders/world.frag");
        program.attach(fragment, gfx::ShaderType::Fragment);

        program.link();
    }

    void WorldRenderer::update(const util::Camera& camera, const world::World& game_world) {
        program.use();
        program.set_uniform("projection", camera.get_projection_matrix());
        program.set_uniform("view", camera.get_view_matrix());

        // Update world vertex array...
    }

    void WorldRenderer::draw() const {
        program.use();

        // Draw world vertex array...
    }
}
