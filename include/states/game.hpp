#pragma once

#include "fps.hpp"
#include "camera.hpp"
#include "states/state.hpp"
#include "gfx/shader.hpp"
#include "gfx/vbo.hpp"
#include "gfx/vao.hpp"

namespace states {
    class Game : public State {
    public:
        Game();
        std::optional<std::unique_ptr<State>> update(Window& window, double delta) override;
        void draw() const override;

    private:
        Camera camera;
        gfx::ShaderProgram program;
        gfx::VertexBuffer vbo;
        gfx::VertexArray vao;
        FramesPerSecond fps;
        bool wireframe = false;
    };
}
