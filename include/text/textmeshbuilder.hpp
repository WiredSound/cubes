#pragma once

#include "text/textmesh.hpp"
#include "util/vertex.hpp"
#include "util/meshbuilder.hpp"

namespace text {
    class TextMeshBuilder : public util::MeshBuilder<util::Position2Texel2, TextMesh, 4> {
    public:
        TextMeshBuilder(const std::string& text);

    protected:
        std::string vertex_to_string(const util::Position2Texel2& vertex) override;

        std::array<float, 4> vertex_to_data(const util::Position2Texel2& vertex) override;
    };
}
