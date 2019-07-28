#pragma once

#include <utility>

#include <entt/entity/registry.hpp>

#include <Core/Core.hpp>

#include "SharedState.hpp"

namespace game
{
class System
{
public:
    explicit System(core::Core &core)
        : m_core{core}
    {
    }

    virtual ~System() = default;

protected:
    inline core::Core &getCore()
    {
        return m_core;
    }

private:
    core::Core &m_core;
};

}  // namespace game
