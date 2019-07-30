#pragma once

#include <Core/Core.hpp>
#include <Core/Rendering/RenderingQueue.hpp>

#include <entt/entity/registry.hpp>
#include <entt/signal/dispatcher.hpp>

#include "Game/Stuff/SceneEvents.hpp"

namespace game
{
class SharedState
{
public:
    explicit SharedState(core::Core &core, entt::registry &registry, entt::dispatcher &dispatcher);

    virtual ~SharedState() = default;

    inline core::Core &getCore();

    inline entt::registry &getRegistry();

    inline entt::dispatcher &getDispatcher();

    inline core::RenderingQueue &getRenderingQueue();

private:
    core::Core &m_core;
    entt::registry &m_registry;
    entt::dispatcher &m_dispatcher;

    core::RenderingQueue m_renderingQueue;
};


core::Core &SharedState::getCore()
{
    return m_core;
}


entt::registry &SharedState::getRegistry()
{
    return m_registry;
}


entt::dispatcher &SharedState::getDispatcher()
{
    return m_dispatcher;
}


core::RenderingQueue &SharedState::getRenderingQueue()
{
    return m_renderingQueue;
}

}  // namespace game
