#pragma once

#include <glm/glm.hpp>

#include "util/hash.hpp"

namespace util {
    struct Position3Colour3 {
        glm::vec3 position;
        glm::vec3 colour;

        bool operator==(const Position3Colour3& other) const;
    };

    struct Position2Texel2 {
        glm::vec2 position;
        glm::vec2 texture_coords;

        bool operator==(const Position2Texel2& other) const;
    };
}

namespace std {
    template <>
    struct hash<util::Position3Colour3> {
        std::size_t operator()(const util::Position3Colour3& v) const noexcept {
            std::size_t seed = 0;
            util::hash_combine(seed, std::hash<glm::vec3>{}(v.position));
            util::hash_combine(seed, std::hash<glm::vec3>{}(v.colour));
            return seed;
        }
    };

    template <>
    struct hash<util::Position2Texel2> {
        std::size_t operator()(const util::Position2Texel2& v) const noexcept {
            std::size_t seed = 0;
            util::hash_combine(seed, std::hash<glm::vec2>{}(v.position));
            util::hash_combine(seed, std::hash<glm::vec2>{}(v.texture_coords));
            return seed;
        }
    };
}
