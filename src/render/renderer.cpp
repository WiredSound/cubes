#include <glad/glad.h>

#include "render/renderer.hpp"

namespace render {
    void Renderer::update(const util::Camera& camera, const world::World& game_world) {
        world_renderer.update(camera, game_world);
    }

    void Renderer::draw(bool wireframe) const {
        if(wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // Draw text...

        if(wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        world_renderer.draw();
    }
}
