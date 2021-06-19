#pragma once

#include <glm/glm.hpp>

#include <string>
#include <cstddef>

// Forward declaration.
namespace render { class DebugTextRenderer; }

namespace text {
    enum class DebugTextLine {
        FramesPerSecond = 0, // 1st line
        PolygonMode, // 2nd line
        CameraCoordinates, // 3nd line
        ChunksLoaded // 4rd line
    };

    class DebugText {
    public:
        void update_fps(float fps, render::DebugTextRenderer& renderer) const;
        void update_polygon_mode(bool wireframe, render::DebugTextRenderer& renderer) const;
        void update_camera_coords(const glm::vec3& coords, render::DebugTextRenderer& renderer) const;
        void update_chunks_loaded(std::size_t count, render::DebugTextRenderer& renderer) const;

    private:
        void set_line(DebugTextLine line, std::string text, render::DebugTextRenderer& renderer) const;
    };
}
