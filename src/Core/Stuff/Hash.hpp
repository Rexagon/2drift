#pragma once

#include <functional>

namespace core::hash
{
template <typename T>
inline void combine(std::size_t &seed, const T &val)
{
    std::hash<T> hasher{};
    seed ^= hasher(val) + 0x9e3779b9 + (seed << 6u) + (seed >> 2u);
}

}  // namespace core::hash
