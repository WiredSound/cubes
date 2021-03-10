#pragma once

#include <glm/glm.hpp>

#include "util/hash.hpp"

namespace util {
    struct VertexColour {
        glm::vec3 vertex;
        glm::vec3 colour;

        bool operator==(const VertexColour& other) const;
    };
}

namespace std {
    template <>
    struct hash<util::VertexColour> {
        std::size_t operator()(const util::VertexColour& v) const noexcept {
            std::size_t seed = 0;
            util::hash_combine(seed, std::hash<glm::vec3>{}(v.vertex));
            util::hash_combine(seed, std::hash<glm::vec3>{}(v.colour));
            return seed;
        }
    };
}
