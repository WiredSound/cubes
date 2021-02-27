#pragma once

#include "util/camera.hpp"
#include "world/world.hpp"
#include "render/worldrenderer.hpp"

namespace render {
    class Renderer {
    public:
        void update(const util::Camera& camera, const world::World& world);
        void draw(bool wireframe) const;

    private:
        WorldRenderer world_renderer;
    };
}
