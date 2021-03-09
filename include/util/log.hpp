#pragma once

#include <string>
#include <iostream>

#define LOG(msg) std::cout << "[INFO] " << msg << std::endl
#define LOG_TRACE(msg) std::cout << "[TRACE] " << msg << std::endl
#define LOG_ERROR(msg) std::cerr << "[ERROR] " << msg << std::endl

namespace util {
    template <typename T>
    std::string vec3_to_string(const T& vec) {
        return "(" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + ")";
    }
}
