#pragma once

#include <vector>

#include <Core/Managers/SceneManager.hpp>

#include "SceneEvents.hpp"
#include "SharedState.hpp"
#include "System.hpp"

namespace game
{
template <typename T>
class Scene final : public core::Scene
{
public:
    static_assert(std::is_base_of_v<SharedState, T>, "T must be a child class of SharedState");

    explicit Scene(core::Core &core)
        : core::Scene{core}
        , m_sharedState{core, m_registry, m_dispatcher}
    {
    }

private:
    void update(double dt) override
    {
        for (auto &system : m_systems)
        {
            system->update(m_sharedState, dt);
        }
    }

    entt::registry m_registry;
    entt::dispatcher m_dispatcher{};

    T m_sharedState;

    std::vector<std::unique_ptr<System>> m_systems;
};

}  // namespace game
