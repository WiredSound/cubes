#pragma once

#include "states/state.hpp"
#include "util/fps.hpp"
#include "util/camera.hpp"
#include "world/world.hpp"
#include "render/renderer.hpp"

namespace states {
    class Game : public State {
    public:
        Game(gfx::Window& window);
        std::optional<std::unique_ptr<State>> update(gfx::Window& window, double delta) override;
        void draw() const override;

    private:
        util::Camera camera;
        world::World game_world;
        util::FramesPerSecond fps;
        render::Renderer renderer;
        bool wireframe;
    };
}
