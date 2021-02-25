#pragma once

#include <glm/glm.hpp>

#include <optional>
#include <memory>
#include <string>

#include "gfx/window.hpp"

namespace states {
    class State {
    protected:
        State(std::string title, glm::vec3 clear_colour);

    public:
        /// Where all game logic is handled for this state. If the returned optional is not empty, then a state
        /// transition will be performed.
        virtual std::optional<std::unique_ptr<State>> update(gfx::Window& window, double delta) = 0;
        /// Handles rendering via OpenGL. Can assume the screen has been cleared before this method is called.
        virtual void draw() const = 0;

        const std::string title;
        const glm::vec3 clear_colour;
    };
}
