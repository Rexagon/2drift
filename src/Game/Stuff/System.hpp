#pragma once

#include <utility>

#include <entt/entity/registry.hpp>

#include <Core/Core.hpp>

#include "SharedState.hpp"

namespace game
{
template <typename T>
class System
{
public:
    static_assert(std::is_base_of_v<SharedState, T>, "T must be a child class of SharedState");

    explicit System(T &state);

    virtual ~System() = default;

    virtual void update(T &t, double dt) = 0;

protected:
    inline T &getState();

private:
    T &m_state;
};


template <typename T>
System<T>::System(T &state)
    : m_state{state}
{
}


template <typename T>
inline T &System<T>::getState()
{
    return m_state;
}


}  // namespace game
