#include "render/debugtextrenderer.hpp"
#include "text/textmeshbuilder.hpp"

namespace render {
    DebugTextRenderer::DebugTextRenderer() : texture("assets/font.png") {
        gfx::Shader vertex("assets/shaders/text.vert", gfx::ShaderType::Vertex);
        program.attach(vertex);

        gfx::Shader fragment("assets/shaders/text.frag", gfx::ShaderType::Fragment);
        program.attach(fragment);

        program.link();
    }

    void DebugTextRenderer::draw() const {
        program.use();
        program.set_uniform("tint", glm::vec3(1.0f, 0.3f, 0.3f));
        texture.bind();

        for(const auto& pair : text_meshes) {
            pair.second.bind_and_draw();
        }
    }

    void DebugTextRenderer::update_text_mesh(text::DebugTextLine line, const std::string& msg) {
        text_meshes.erase(line);
        text_meshes[line] = text::TextMeshBuilder(msg).build();
    }
}
