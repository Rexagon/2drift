#pragma once

#include <functional>

namespace app::stuff
{
template <typename T>
inline void hashCombine(std::size_t &seed, const T &val)
{
    std::hash<T> hasher;
    seed ^= hasher(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

}  // namespace app::stuff
