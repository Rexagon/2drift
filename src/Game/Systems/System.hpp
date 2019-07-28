#pragma once

#include <entt/entity/registry.hpp>

#include <Core/Core.hpp>

namespace game
{
class System
{
public:
    explicit System(core::Core &core);

    virtual ~System() = default;

    virtual void update(entt::registry &registry, double dt) = 0;

protected:
    core::Core &getCore();

private:
    core::Core &m_core;
};

}  // namespace game
