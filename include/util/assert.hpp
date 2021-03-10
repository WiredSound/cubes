#pragma once

#include <cassert>

#ifdef ENABLE_DEBUG_ASSERT
#define DEBUG_ASSERT(assertion) assert(assertion)
#else
#define DEBUG_ASSERT(assertion)
#endif
