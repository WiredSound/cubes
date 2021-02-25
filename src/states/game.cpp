#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <vector>

#include "log.hpp"
#include "states/game.hpp"

namespace states {
    Game::Game(gfx::Window& window) : State("game", glm::vec3(0.0f, 0.0f, 1.0f)), vbo(GL_ARRAY_BUFFER, false), fps(1.0) {
        window.toggle_cursor_lock();

        try {
            gfx::Shader vert("test.vert", gfx::ShaderType::Vertex);
            gfx::Shader frag("test.frag", gfx::ShaderType::Fragment);
            program.attach(vert);
            program.attach(frag);
            program.link();
        }
        catch(std::exception& err) {
            LOG_ERROR("Failed to load shaders: " << err.what());
        }

        std::vector<float> vertices = {
            0.0f, 0.8f, -2.0f,
            0.5f, -0.5f, -2.0f,
            -0.5f, -0.5f, -2.0f
        };

        vbo.data(vertices);
        // Position attribute:
        vao.attribute(vbo, 0, 3, GL_FLOAT);
    }

    std::optional<std::unique_ptr<State>> Game::update(gfx::Window& window, double delta) {
        if(window.was_key_just_pressed(GLFW_KEY_F1)) {
            wireframe = !wireframe;
            LOG((wireframe ? "Enabled" : "Disabled") << " wireframe drawing");
        }

        float deltaf = static_cast<float>(delta);
        if(window.is_key_down(GLFW_KEY_W)) camera.move_towards(util::Direction::Forward, deltaf);
        if(window.is_key_down(GLFW_KEY_S)) camera.move_towards(util::Direction::Backward, deltaf);
        if(window.is_key_down(GLFW_KEY_A)) camera.move_towards(util::Direction::Left, deltaf);
        if(window.is_key_down(GLFW_KEY_D)) camera.move_towards(util::Direction::Right, deltaf);

        glm::vec2 mouse_movement = window.locked_cursor_movement();
        camera.rotate(mouse_movement.x * deltaf, -mouse_movement.y * deltaf);

        if(fps.update(delta)) {
            LOG("FPS: " << fps.get());
        }

        return {}; // Don't want to change state so return empty optional.
    }

    void Game::draw() const {
        if(wireframe) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }

        // Draw game world...

        program.use();
        program.set_uniform("projection", camera.get_projection_matrix());
        program.set_uniform("view", camera.get_view_matrix());

        vao.bind();

        glDrawArrays(GL_TRIANGLES, 0, 3);

        if(wireframe) { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }

        // Draw text...
    }
}
