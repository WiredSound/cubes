#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <memory>
#include <stdexcept>
#include <optional>

#include "util/log.hpp"
#include "util/init.hpp"
#include "gfx/window.hpp"
#include "states/state.hpp"
#include "states/game.hpp"

int main() {
    util::InitGLFW glfw;
    gfx::Window window;

    try {
        glfw.init();
        window.create(800, 600, "Cubes", false);
        util::init_gl();
    }
    catch(std::exception& err) {
        LOG_ERROR("Initialisation failed - " << err.what());
        return -1;
    }

    std::unique_ptr<states::State> current_state;
    std::optional<std::unique_ptr<states::State>> possible_state_change;

    try {
        current_state = std::make_unique<states::Game>(window);
    }
    catch(std::exception& err) {
        LOG_ERROR("Failed to enter initial game state due to error - " << err.what());
        return -1;
    }

    float loop_start_time = 0.0, delta = 0.0;

    LOG("Entering main loop in state '" << current_state->title << "'");

    while(window.should_stay_open()) {
        // Get timestamp at start of loop so that the delta may be calculated:
        loop_start_time = static_cast<float>(glfwGetTime());

        // Input & update state:

        if(window.is_key_down(GLFW_KEY_ESCAPE)) {
            window.close();
        }

        possible_state_change = current_state->update(window, delta);

        // Rendering:

        glClearColor(current_state->clear_colour.x, current_state->clear_colour.y, current_state->clear_colour.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        current_state->draw();

        window.draw_and_update();

        // Handle state transition (if any):

        if(possible_state_change && possible_state_change.value()) {
            LOG("Transitioning state from '" << current_state->title << "' to '" << possible_state_change.value()->title << "'");
            current_state = std::move(possible_state_change.value());
        }

        // Calculate the time taken for the above to execute:
        delta = static_cast<float>(glfwGetTime()) - loop_start_time;
    }

    LOG("Exited main loop in state '" << current_state->title << "'");

    return 0;
}
