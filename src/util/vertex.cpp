#include "util/vertex.hpp"

namespace util {
    bool Position3Colour3::operator==(const Position3Colour3& other) const {
        return glm::all(glm::equal(position, other.position)) && glm::all(glm::equal(colour, other.colour));
    }
}
