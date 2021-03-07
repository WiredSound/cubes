#include <glad/glad.h>

#include "render/renderer.hpp"

namespace render {
    void Renderer::update(const util::Camera& camera) {
        world_renderer.update(camera);
    }

    void Renderer::draw(bool wireframe) const {
        if(wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // Draw text...

        if(wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        world_renderer.draw();
    }
}
