#include "world/block.hpp"

namespace world {
    const glm::vec3& get_block_colour(const Block& block) {
        switch(block) {
        case Block::Grass: return colours::green;
        default: return colours::black;
        }
    }
}
