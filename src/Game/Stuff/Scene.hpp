#pragma once

#include <experimental/type_traits>
#include <vector>

#include <Core/Managers/SceneManager.hpp>

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

    template <typename S, typename... Args>
    void addSystem(Args &&... args);

    void addSystem(const std::function<void(T &, double)> &system);

    inline T &getState();

private:
    void update(double dt) override;

    void onInit() override;

    void onClose() override;

    void onEnter() override;

    void onLeave() override;

    void handleEvent(const sf::Event &e) override;

    entt::registry m_registry;
    entt::dispatcher m_dispatcher{};

    T m_sharedState;

    std::vector<std::function<void(T &, double)>> m_systems{};
};


template <typename T>
Scene<T>::Scene(core::Core &core)
    : core::Scene{core}
    , m_sharedState{core, m_registry, m_dispatcher}
{
}


template <typename T>
template <typename S, typename... Args>
void Scene<T>::addSystem(Args &&... args)
{
    m_systems.emplace_back(S{m_sharedState, std::forward<Args>(args)...});
}


template <typename T>
void Scene<T>::addSystem(const std::function<void(T &, double)> &system)
{
    m_systems.emplace_back(system);
}


template <typename T>
inline T &Scene<T>::getState()
{
    return m_sharedState;
}


template <typename T>
void Scene<T>::update(double dt)
{
    for (auto &updater : m_systems)
    {
        updater(m_sharedState, dt);
    }
}


template <typename T>
void Scene<T>::onInit()
{
    m_sharedState.getDispatcher().template trigger<events::OnInitScene>();
}


template <typename T>
void Scene<T>::onClose()
{
    m_sharedState.getDispatcher().template trigger<events::OnCloseScene>();
}


template <typename T>
void Scene<T>::onEnter()
{
    m_sharedState.getDispatcher().template trigger<events::OnEnterScene>();
}


template <typename T>
void Scene<T>::onLeave()
{
    m_sharedState.getDispatcher().template trigger<events::OnLeaveScene>();
}


template <typename T>
void Scene<T>::handleEvent(const sf::Event &e)
{
    m_sharedState.getDispatcher().template trigger<sf::Event>(e);
}

}  // namespace game
