// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "SharedState.hpp"

namespace game
{
SharedState::SharedState(core::Core &core, entt::registry &registry, entt::dispatcher &dispatcher)
    : m_core{core}
    , m_registry{registry}
    , m_dispatcher{dispatcher}
{
}

}  // namespace game
