#pragma once

#include <string>
#include <unordered_map>

#include "gfx/shader.hpp"
#include "gfx/texture.hpp"
#include "text/textmesh.hpp"
#include "text/debugtext.hpp"

namespace render {
    class DebugTextRenderer {
    public:
        DebugTextRenderer(int window_width, int window_height);
        void draw() const;
        void window_resized(int width, int height);

    private:
        // `text::DebugText` is a friend so that only that class can update/remove text meshes.
        friend text::DebugText;

        void update_text_mesh(
            text::DebugTextLine line, const std::string& msg
        );

        int window_width, window_height;

        gfx::Texture texture;

        gfx::ShaderProgram program;

        /// Map between text lines and coresponding meshes.
        std::unordered_map<text::DebugTextLine, text::TextMesh> text_meshes;
    };
}
