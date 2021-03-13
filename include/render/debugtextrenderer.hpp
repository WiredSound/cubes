#pragma once

#include <unordered_map>

#include "gfx/shader.hpp"
#include "text/textmesh.hpp"
#include "text/debugtext.hpp"

namespace render {
    class DebugTextRenderer {
    public:
        DebugTextRenderer();
        void draw() const;

    private:
        // `text::DebugText` is a friend so that only that class can update/remove text meshes.
        friend text::DebugText;

        gfx::ShaderProgram program;

        /// Map between text ID numbers and their coresponding meshes.
        std::unordered_map<unsigned int, text::TextMesh> text_meshes;
    };
}
