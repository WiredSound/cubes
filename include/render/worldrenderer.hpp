#pragma once

#include "util/camera.hpp"
#include "world/world.hpp"
#include "gfx/shader.hpp"

namespace render {
    class WorldRenderer {
    public:
        WorldRenderer();
        void update(const util::Camera& camera, const world::World& game_world);
        void draw() const;

    private:
        ShaderProgram program;
    };
}
