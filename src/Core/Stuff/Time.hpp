#pragma once

#include <chrono>
#include <functional>

namespace core::time
{
using DurationSeconds = std::chrono::duration<float>;
using DurationMilliseconds = std::chrono::duration<uint64_t, std::milli>;
using DurationNanoseconds = std::chrono::duration<uint64_t, std::nano>;


inline auto now() -> auto
{
    return std::chrono::high_resolution_clock::now();
}


struct Benchmark
{
public:
    Benchmark(const std::function<void()> &f);
    Benchmark(const std::string &name, const std::function<void()> &f);
};

}  // namespace core::time
