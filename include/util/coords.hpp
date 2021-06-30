#pragma once

#include <glm/glm.hpp>

#include <string>

namespace util {
    template <typename T>
    std::string coords_to_string(const glm::tvec2<T>& vec) {
        return "(" + std::to_string(vec.x) + ", " + std::to_string(vec.y);
    }

    template <typename T>
    std::string coords_to_string(const glm::tvec3<T>& vec) {
        return "(" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + ")";
    }

    template <typename T>
    glm::tvec3<T> coords_above(glm::tvec3<T> coords, T change = 1) {
        coords.y += change;
        return coords;
    }

    template <typename T>
    glm::tvec3<T> coords_below(glm::tvec3<T> coords, T change = 1) {
        coords.y -= change;
        return coords;
    }

    template <typename T>
    glm::tvec3<T> coords_left(glm::tvec3<T> coords, T change = 1) {
        coords.x -= change;
        return coords;
    }

    template <typename T>
    glm::tvec3<T> coords_right(glm::tvec3<T> coords, T change = 1) {
        coords.x += change;
        return coords;
    }

    template <typename T>
    glm::tvec3<T> coords_front(glm::tvec3<T> coords, T change = 1) {
        coords.z -= change;
        return coords;
    }

    template <typename T>
    glm::tvec3<T> coords_rear(glm::tvec3<T> coords, T change = 1) {
        coords.z += change;
        return coords;
    }
}
