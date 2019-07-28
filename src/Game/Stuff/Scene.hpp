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

    explicit Scene(core::Core &core);

    template <typename S>
    void addSystem(std::unique_ptr<S> system);

    template <typename S>
    void addSystem(std::function<void(S &, double)> function);

    inline T &getState();

private:
    void update(double dt) override;

    entt::registry m_registry;
    entt::dispatcher m_dispatcher{};

    T m_sharedState;

    std::vector<std::unique_ptr<System>> m_systems{};

    std::vector<std::function<void(T &, double)>> m_systemUpdaters{};
};


template <typename T>
Scene<T>::Scene(core::Core &core)
    : core::Scene{core}
    , m_sharedState{core, m_registry, m_dispatcher}
{
}


template <typename T>
template <typename Sy>
void Scene<T>::addSystem(std::unique_ptr<Sy> system)
{
    static_assert(std::is_base_of_v<System, Sy>, "Sy must be a child class of System");

    auto *ptr = system.get();
    m_systemUpdaters.emplace_back([ptr](T &state, double dt) { ptr->update(state, dt); });

    m_systems.emplace_back(std::move(system));
}


template <typename T>
template <typename St>
void Scene<T>::addSystem(std::function<void(St &, double)> function)
{
    static_assert(std::is_base_of_v<St, T>, "St must be a equal to T or be a base class of T");

    m_systemUpdaters.emplace_back(function);
}


template <typename T>
inline T &Scene<T>::getState()
{
    return m_sharedState;
}


template <typename T>
void Scene<T>::update(double dt)
{
    for (auto &updater : m_systemUpdaters)
    {
        updater(m_sharedState, dt);
    }
}

}  // namespace game
