#pragma once

#include <glm/glm.hpp>

#include <cstddef>
#include <functional>

namespace util {
    /// Implementation taken from `boost::hash_combine`.
    void hash_combine(std::size_t& seed, std::size_t value);
}

// Implement hashing for `glm::vec3` type:
namespace std {
    template <>
    struct hash<glm::vec3> {
        std::size_t operator()(const glm::vec3& v) const noexcept {
            size_t seed = 0;
            util::hash_combine(seed, hash<float>{}(v.x));
            util::hash_combine(seed, hash<float>{}(v.y));
            util::hash_combine(seed, hash<float>{}(v.z));
            return seed;
        }
    };
}
