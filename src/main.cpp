#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <memory>
#include <stdexcept>
#include <optional>

#include "log.hpp"
#include "init.hpp"
#include "window.hpp"
#include "states/state.hpp"
#include "states/game.hpp"

int main() {
    InitGLFW glfw;
    Window window;

    try {
        glfw.init();

        window.create(800, 600, "OpenGL Template C++", false);

        init_gl();
    }
    catch(std::exception& err) {
        LOG_ERROR("Initialisation failed - " << err.what());
        return -1;
    }

    std::unique_ptr<states::State> current_state = std::make_unique<states::Game>();
    std::optional<std::unique_ptr<states::State>> possible_state_change;

    double loop_start_time = 0.0, delta = 0.0;

    LOG("Entering main loop in state '" << current_state->title << "'");

    while(window.should_stay_open()) {
        // Get timestamp at start of loop so that the delta may be calculated:
        loop_start_time = glfwGetTime();

        // Input & update state:

        if(window.is_key_down(GLFW_KEY_ESCAPE)) {
            window.close();
        }

        possible_state_change = current_state->update(window, delta);

        // Rendering:

        glClearColor(current_state->clear_colour.x, current_state->clear_colour.y, current_state->clear_colour.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        current_state->draw();

        window.draw_and_update();

        // Handle state transition (if any):

        if(possible_state_change && possible_state_change.value()) {
            LOG("Transitioning state from '" << current_state->title << "' to '" << possible_state_change.value()->title << "'");
            current_state = std::move(possible_state_change.value());
        }

        // Calculate the time taken for the above to execute:
        delta = glfwGetTime() - loop_start_time;
    }

    LOG("Exited main loop in state '" << current_state->title << "'");

    return 0;
}
