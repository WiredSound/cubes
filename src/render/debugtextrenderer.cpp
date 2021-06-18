#include "render/debugtextrenderer.hpp"

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
        glActiveTexture(GL_TEXTURE0);
        texture.bind();

        for(const auto& pair : text_meshes) {
            pair.second.bind_and_draw();
        }
    }

    void DebugTextRenderer::update_text_mesh(text::DebugTextLine line, const std::string& msg) {
        text_meshes[line] = text::TextMesh();
        std::vector<float> vertices = {
            0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            0.0f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f
        };
        std::vector<unsigned int> indices = {0, 1, 2, 1, 2, 3};
        text_meshes[line].create(vertices, indices);
    }
}
