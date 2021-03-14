#pragma once

#include <iostream>

#define LOG(msg) std::cout << "[INFO] " << msg << std::endl
#define LOG_ERROR(msg) std::cerr << "[ERROR] " << msg << std::endl

#ifdef ENABLE_LOG_TRACE
#define LOG_TRACE(msg) std::cout << "[TRACE] " << msg << std::endl
#else
#define LOG_TRACE(MSG)
#endif
