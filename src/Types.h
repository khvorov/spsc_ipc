#pragma once

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/lockfree/spsc_queue.hpp>

// #define USE_APPLE_CLOCKS

#if defined(USE_APPLE_CLOCKS) && (defined(__APPLE__) || defined(__MACH__))
#include <mach/mach_time.h>
#else
#include <chrono>
#endif

#include <cstdint>

namespace bip = boost::interprocess;

namespace shm {

using RingBuffer = boost::lockfree::spsc_queue<int64_t, boost::lockfree::capacity<1024>>;

#if defined(USE_APPLE_CLOCKS) && (defined(__APPLE__) || defined(__MACH__))
int64_t Now()
{
    uint64_t ticks = mach_absolute_time();
    return ticks;
}
#else
int64_t Now()
{
    auto tse = std::chrono::steady_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(tse).count();
}
#endif

}
