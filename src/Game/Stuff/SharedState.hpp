#pragma once

#include <Core/Core.hpp>
#include <Core/Rendering/Stuff/RenderingQueue.hpp>
#include <Core/Resources/Stuff/ResourcesScope.hpp>

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

    inline core::ResourcesScope &getResourcesScope();

private:
    core::Core &m_core;
    entt::registry &m_registry;
    entt::dispatcher &m_dispatcher;

    core::RenderingQueue m_renderingQueue;
    core::ResourcesScope m_resourcesScope;
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


core::ResourcesScope &SharedState::getResourcesScope()
{
    return m_resourcesScope;
}

}  // namespace game
