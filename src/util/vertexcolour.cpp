#include "util/vertexcolour.hpp"

namespace util {
    bool VertexColour::operator==(const VertexColour& other) const {
        return glm::all(glm::equal(vertex, other.vertex)) && glm::all(glm::equal(colour, other.colour));
    }
}
