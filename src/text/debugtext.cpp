#include "util/coords.hpp"
#include "text/debugtext.hpp"
#include "render/debugtextrenderer.hpp"

namespace text {
    void DebugText::update_fps(float fps, render::DebugTextRenderer& renderer) const {
        set_line(DebugTextLine::FramesPerSecond, "FPS: " + std::to_string(fps), renderer);
    }

    void DebugText::update_polygon_mode(bool wireframe, render::DebugTextRenderer& renderer) const {
        set_line(DebugTextLine::PolygonMode, "Polygon mode: " + std::string(wireframe ? "Wireframe" : "Normal"), renderer);
    }

    void DebugText::update_camera_coords(const glm::vec3& coords, render::DebugTextRenderer& renderer) const {
        set_line(DebugTextLine::CameraCoordinates, "Position: " + util::coords_to_string(coords), renderer);
    }

    void DebugText::update_chunks_loaded(std::size_t count, render::DebugTextRenderer& renderer) const {
        set_line(DebugTextLine::ChunksLoaded, "Chunks loaded: " + std::to_string(count), renderer);
    }

    void DebugText::set_line(DebugTextLine line, std::string text, render::DebugTextRenderer& renderer) const {
        renderer.update_text_mesh(line, text);
    }
}
