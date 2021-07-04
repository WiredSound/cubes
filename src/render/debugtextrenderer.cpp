#include "render/debugtextrenderer.hpp"
#include "text/textmeshbuilder.hpp"

const unsigned int FONT_IMAGE_WIDTH = 128, FONT_IMAGE_HEIGHT = 48, FONT_CHARACTER_WIDTH = 8, FONT_CHARACTER_HEIGHT = 8,
                   FONT_CHARACTERS_PER_ROW = 16;
const float FONT_DRAW_SCALE_FACTOR = 5.0;

namespace render {
    DebugTextRenderer::DebugTextRenderer(int window_width, int window_height)
    : window_width(window_width), window_height(window_height), texture("assets/font.png") {
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

        if(text_meshes.find(text::DebugTextLine::CameraCoordinates) != text_meshes.end())
            text_meshes.at(text::DebugTextLine::CameraCoordinates).bind_and_draw();
        /*float draw_y = 0.48;
        for(const auto& pair : text_meshes) {
            //proram.set_uniform("position", glm::vec2(-0.48, draw_y));
            pair.second.bind_and_draw();
            draw_y -= static_cast<float>(FONT_CHARACTER_HEIGHT) / static_cast<float>(window_height);
        }*/
    }

    void DebugTextRenderer::window_resized(int width, int height) {
        window_width = width;
        window_height = height;
        // TODO: Rebuild all meshes.
    }

    void DebugTextRenderer::update_text_mesh(
        text::DebugTextLine line, const std::string& msg
    ) {
        text_meshes.erase(line);
        text::TextMeshBuilder builder(
            msg, window_width, window_height, FONT_IMAGE_WIDTH, FONT_IMAGE_HEIGHT, FONT_CHARACTER_WIDTH,
            FONT_CHARACTER_HEIGHT, FONT_CHARACTERS_PER_ROW, FONT_DRAW_SCALE_FACTOR
        );
        text_meshes[line] = builder.build();
    }
}
