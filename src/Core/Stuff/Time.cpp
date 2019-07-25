// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Time.hpp"

#include <iostream>

namespace core::time
{
Benchmark::Benchmark(const std::function<void()> &f)
    : Benchmark("Unnamed", f)
{
}

Benchmark::Benchmark(const std::string &name, const std::function<void()> &f)
{
    const auto before = now();
    f();
    const auto after = now();

    std::cout << name << " benchmark result: " << DurationNanoseconds{after - before}.count() << "ns" << std::endl;
}

}  // namespace core::time
