#pragma once

#include <tuple>
#include <vector>

#include <Core/Managers/SceneManager.hpp>
#include <Core/Stuff/Tag.hpp>

#include "SharedState.hpp"
#include "System.hpp"

namespace game
{
template <typename... S>
using Systems = core::Tags<S...>;

template <typename T, typename>
class Scene;

template <typename T, typename... S>
class Scene<T, Systems<S...>> final : public core::Scene
{
public:
    static_assert(std::is_base_of_v<SharedState, T>, "T must be a child class of SharedState");
    static_assert(sizeof...(S) > 0, "Scene must have at least one system");

    explicit Scene(core::Core &core);

    inline T &getState();

private:
    void update(double dt) override;

    void init() override;

    void close() override;

    void handleEvent(const sf::Event &e) override;

    entt::registry m_registry{};
    entt::dispatcher m_dispatcher{};

    T m_state;

    std::tuple<S...> m_systems;
};


template <typename T, typename... S>
Scene<T, Systems<S...>>::Scene(core::Core &core)
    : core::Scene{core}
    , m_state{core, m_registry, m_dispatcher}
    , m_systems{(core::Tag<S>{}, m_state)...}
{
}


template <typename T, typename... S>
inline T &Scene<T, Systems<S...>>::getState()
{
    return m_state;
}


template <typename T, typename... S>
void Scene<T, Systems<S...>>::init()
{
    m_state.getDispatcher().template trigger<events::OnInitScene>();
}


template <typename T, typename... S>
void Scene<T, Systems<S...>>::close()
{
    m_state.getDispatcher().template trigger<events::OnCloseScene>();
}


template <typename T, typename... S>
void Scene<T, Systems<S...>>::handleEvent(const sf::Event &e)
{
    m_state.getDispatcher().template trigger<sf::Event>(e);
}


template <typename T, typename... S>
void Scene<T, Systems<S...>>::update(double dt)
{
    using dummy = int[];
    dummy{(std::get<S>(m_systems).update(m_state, dt), 0)..., 0};
}


}  // namespace game
