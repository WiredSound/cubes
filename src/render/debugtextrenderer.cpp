#include "render/debugtextrenderer.hpp"

namespace render {
    DebugTextRenderer::DebugTextRenderer() {
        gfx::Shader vertex("assets/shaders/text.vert", gfx::ShaderType::Vertex);
        program.attach(vertex);

        gfx::Shader fragment("assets/shaders/text.frag", gfx::ShaderType::Fragment);
        program.attach(fragment);

        program.link();
    }

    void DebugTextRenderer::draw() const {
        // TODO
    }

    void DebugTextRenderer::update_text_mesh(text::DebugTextLine line, const std::string& msg) {
        // TODO
    }
}
