#include "util/log.hpp"
#include "text/debugtext.hpp"
#include "render/debugtextrenderer.hpp"

namespace text {
    void DebugText::update_fps(float fps, render::DebugTextRenderer& renderer) {
        set_line(DebugTextLine::FramesPerSecond, "FPS: " + std::to_string(fps), renderer);
    }

    void DebugText::update_camera_coords(const glm::vec3& coords, render::DebugTextRenderer& renderer) {
        set_line(DebugTextLine::CameraCoordinates, "Position: " + util::vec3_to_string(coords), renderer);
    }

    void DebugText::update_chunks_loaded(std::size_t count, render::DebugTextRenderer& renderer) {
        set_line(DebugTextLine::ChunksLoaded, "Chunks loaded: " + std::to_string(count), renderer);
    }

    void DebugText::set_line(DebugTextLine line, std::string text, render::DebugTextRenderer& renderer) {
        renderer.update_text_mesh(line, text);
    }
}
