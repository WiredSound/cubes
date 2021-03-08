#pragma once

#include <glm/glm.hpp>

namespace world {
    enum class Block : unsigned char { None, Grass };

    namespace colours {
        constexpr glm::vec3 black(0.0f);
        constexpr glm::vec3 green(0.373f, 0.757f, 0.0f);
    }

    const glm::vec3& get_block_colour(const Block& block);
}
