#include "text/textmeshbuilder.hpp"
#include "util/coords.hpp"

namespace text {
    std::string TextMeshBuilder::vertex_to_string(const util::Position2Texel2& vertex) {
        return "pos: " + util::coords_to_string(vertex.position) + " texel: " + util::coords_to_string(vertex.texture_coords);
    }


    std::array<float, 4> TextMeshBuilder::vertex_to_data(const util::Position2Texel2& vertex) {
        return {
            vertex.position.x, vertex.position.y,
            vertex.texture_coords.x, vertex.texture_coords.y
        };
    }
}
