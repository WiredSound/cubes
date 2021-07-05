#pragma once

#include <iostream>

#define ADDITIONAL_LOG_INFO(level) "[" << level << " - " << __FILE__ << " @ " << __LINE__ << "] "

#define LOG(msg) std::cout << ADDITIONAL_LOG_INFO("INFO") << msg << std::endl
#define LOG_ERROR(msg) std::cerr << ADDITIONAL_LOG_INFO("ERROR") << msg << std::endl

#ifdef ENABLE_LOG_TRACE
#define LOG_TRACE(msg) std::cout << ADDITIONAL_LOG_INFO("TRACE") << msg << std::endl
#else
#define LOG_TRACE(MSG)
#endif
