#include <GLFW/glfw3.h>

#include "states/game.hpp"
#include "util/log.hpp"

namespace states {
    Game::Game(gfx::Window& window) : State("game", glm::vec3(0.46f, 0.74f, 0.85f)), fps(1.0) {
        window.toggle_cursor_lock();

        std::unordered_map<glm::ivec3, world::Chunk> chunks;
        chunks.emplace(glm::ivec3(0, 0, 0), world::Chunk(world::Block::Grass));
        chunks.emplace(glm::ivec3(1, 0, 0), world::Chunk(world::Block::Grass));
        chunks.emplace(glm::ivec3(2, 0, 0), world::Chunk(world::Block::Grass));

        game_world.provide_chunks(std::move(chunks), renderer, debug_text);
    }

    std::optional<std::unique_ptr<State>> Game::update(gfx::Window& window, float delta) {
        if(window.is_key_down(GLFW_KEY_W))
            camera.move_towards(util::Direction::Forward, delta, renderer.debug_text_renderer, debug_text);
        if(window.is_key_down(GLFW_KEY_S))
            camera.move_towards(util::Direction::Backward, delta, renderer.debug_text_renderer, debug_text);
        if(window.is_key_down(GLFW_KEY_A))
            camera.move_towards(util::Direction::Left, delta, renderer.debug_text_renderer, debug_text);
        if(window.is_key_down(GLFW_KEY_D))
            camera.move_towards(util::Direction::Right, delta, renderer.debug_text_renderer, debug_text);
        if(window.is_key_down(GLFW_KEY_SPACE))
            camera.move_towards(util::Direction::Up, delta, renderer.debug_text_renderer, debug_text);
        if(window.is_key_down(GLFW_KEY_LEFT_CONTROL))
            camera.move_towards(util::Direction::Down, delta, renderer.debug_text_renderer, debug_text);

        if(window.was_key_just_pressed(GLFW_KEY_Y)) {
            game_world.provide_chunk(glm::ivec3(1, 0, 1), world::Chunk(world::Block::Grass), renderer, debug_text);
        }

        glm::vec2 mouse_movement = window.locked_cursor_movement();
        camera.rotate(mouse_movement.x * delta, -mouse_movement.y * delta);

        if(window.was_key_just_pressed(GLFW_KEY_F1)) {
            wireframe = !wireframe;

            LOG((wireframe ? "Enabled" : "Disabled") << " wireframe rendering");
            debug_text.update_polygon_mode(wireframe, renderer.debug_text_renderer);
        }

        if(fps.update(delta)) {
            LOG_TRACE("FPS: " << fps.get());
            debug_text.update_fps(delta, renderer.debug_text_renderer);
        }

        renderer.update(camera);

        return {}; // Don't want to change state so return empty optional.
    }

    void Game::draw() const {
        renderer.draw(wireframe);
    }
}
