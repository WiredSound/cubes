#pragma once

#include "util/camera.hpp"
#include "render/worldrenderer.hpp"
#include "render/debugtextrenderer.hpp"

namespace render {
    class Renderer {
    public:
        void update(const util::Camera& camera);
        void draw(bool wireframe) const;

        WorldRenderer world_renderer;
        DebugTextRenderer debug_text_renderer;
    };
}
