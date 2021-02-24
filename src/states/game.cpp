#include <glm/glm.hpp>

#include "log.hpp"
#include "states/game.hpp"

namespace states {
    Game::Game() : State("game", glm::vec3(0.0f, 0.0f, 1.0f)), fps(1.0) {}

    std::optional<std::unique_ptr<State>> Game::update(Window& window, double delta) {
        if(fps.update(delta)) {
            LOG("FPS: " << fps.get());
        }

        return {}; // Don't want to change state so return empty optional.
    }

    void Game::draw() const {}
}
