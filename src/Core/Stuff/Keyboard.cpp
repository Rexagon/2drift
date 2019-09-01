// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Keyboard.hpp"

namespace core::keyboard
{
uint8_t operator|(const Modifier &l, const Modifier &r)
{
    return static_cast<uint8_t>(l) | static_cast<uint8_t>(r);
}


bool operator&(const uint8_t &l, const Modifier &r)
{
    return (l & static_cast<uint8_t>(r)) != 0u;
}

}  // namespace core::keyboard
