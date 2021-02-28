#pragma once

#include <vector>

namespace util {
    struct Mesh {
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
    };
}
