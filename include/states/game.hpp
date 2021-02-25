#pragma once

#include "util/fps.hpp"
#include "util/camera.hpp"
#include "states/state.hpp"
#include "gfx/shader.hpp"
#include "gfx/vbo.hpp"
#include "gfx/vao.hpp"

namespace states {
    class Game : public State {
    public:
        Game(gfx::Window& window);
        std::optional<std::unique_ptr<State>> update(gfx::Window& window, double delta) override;
        void draw() const override;

    private:
        util::Camera camera;
        gfx::ShaderProgram program;
        gfx::VertexBuffer vbo;
        gfx::VertexArray vao;
        util::FramesPerSecond fps;
        bool wireframe = false;
    };
}
