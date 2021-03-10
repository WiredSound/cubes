#include <GLFW/glfw3.h>

#include "states/game.hpp"
#include "util/log.hpp"

namespace states {
    Game::Game(gfx::Window& window) : State("game", glm::vec3(0.46f, 0.74f, 0.85f)), fps(1.0) {
        window.toggle_cursor_lock();

        game_world.provide_chunk(glm::ivec3(0, 0, 0), world::Chunk(world::Block::Grass), renderer.world_renderer);
        game_world.provide_chunk(glm::ivec3(1, 0, 0), world::Chunk(world::Block::Grass), renderer.world_renderer);
    }

    std::optional<std::unique_ptr<State>> Game::update(gfx::Window& window, float delta) {
        if(window.is_key_down(GLFW_KEY_W)) camera.move_towards(util::Direction::Forward, delta);
        if(window.is_key_down(GLFW_KEY_S)) camera.move_towards(util::Direction::Backward, delta);
        if(window.is_key_down(GLFW_KEY_A)) camera.move_towards(util::Direction::Left, delta);
        if(window.is_key_down(GLFW_KEY_D)) camera.move_towards(util::Direction::Right, delta);

        if(window.was_key_just_pressed(GLFW_KEY_F1)) {
            wireframe = !wireframe;
            LOG((wireframe ? "Enabled" : "Disabled") << " wireframe rendering");
        }

        glm::vec2 mouse_movement = window.locked_cursor_movement();
        camera.rotate(mouse_movement.x * delta, -mouse_movement.y * delta);

        if(fps.update(delta)) {
            LOG("FPS: " << fps.get());
        }

        renderer.update(camera);

        return {}; // Don't want to change state so return empty optional.
    }

    void Game::draw() const {
        renderer.draw(wireframe);
    }
}
