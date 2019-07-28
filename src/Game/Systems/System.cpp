// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "System.hpp"

namespace game
{
System::System(core::Core &core)
    : m_core{core}
{
}

core::Core &System::getCore()
{
    return m_core;
}

}  // namespace game
