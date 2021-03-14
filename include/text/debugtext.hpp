#pragma once

#include <glm/glm.hpp>

#include <string>
#include <cstddef>

// Forward declaration.
namespace render { class DebugTextRenderer; }

namespace text {
    enum class DebugTextLine {
        FramesPerSecond = 0, // 1st line
        CameraCoordinates = 1, // 2nd line
        ChunksLoaded = 2 // 3rd line
    };

    class DebugText {
    public:
        // FPS, camera coordinates, number of chunks loaded, coordinates of loaded chunks, etc.

        void update_fps(float fps, render::DebugTextRenderer& renderer);
        void update_camera_coords(const glm::vec3& coords, render::DebugTextRenderer& renderer);
        void update_chunks_loaded(std::size_t count, render::DebugTextRenderer& renderer);

    private:
        void set_line(DebugTextLine line, std::string text, render::DebugTextRenderer& renderer);
    };
}
