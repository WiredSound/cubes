#pragma once

#include "fps.hpp"
#include "states/state.hpp"

namespace states {
    class Game : public State {
    public:
        Game();
        std::optional<std::unique_ptr<State>> update(Window& window, double delta) override;
        void draw() const override;

    private:
        FramesPerSecond fps;
        bool wireframe = false;
    };
}
