#include <glm/glm.hpp>

#include "states/game.hpp"

namespace states {
    Game::Game() : State("game", glm::vec3(0.0f, 0.0f, 1.0f)) {}

    std::optional<std::unique_ptr<State>> Game::update(Window& window, double delta) {
        return {}; // Don't want to change state so return empty optional.
    }

    void Game::draw() const {}
}
