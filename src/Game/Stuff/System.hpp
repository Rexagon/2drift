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

    explicit System(T &state)
    {
    }

    virtual ~System() = default;

    virtual void operator()(T &t, double dt)
    {
    }
};

}  // namespace game
