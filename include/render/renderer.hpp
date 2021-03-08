#pragma once

#include "util/camera.hpp"
#include "render/worldrenderer.hpp"

namespace render {
    class Renderer {
    public:
        void update(const util::Camera& camera);
        void draw(bool wireframe) const;

        WorldRenderer world_renderer;
    };
}
