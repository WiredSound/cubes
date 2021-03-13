#include <glad/glad.h>

#include "render/renderer.hpp"

namespace render {
    void Renderer::update(const util::Camera& camera) {
        world_renderer.update(camera);
    }

    void Renderer::draw(bool wireframe) const {
        if(wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        world_renderer.draw();

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        debug_text_renderer.draw();
    }
}
