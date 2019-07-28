// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "SpriteRenderingSystem.hpp"

#include <Core/Managers/ResourceManager.hpp>

using namespace core;

namespace game
{
SpriteRenderingSystem::SpriteRenderingSystem(Core &core)
    : System{core}
    , m_renderingQueue{core.get<ResourceManager>().lock()->get<RenderingQueue>("rendering_queue")}
{
}


void SpriteRenderingSystem::update(SharedState &state, double dt)
{
    auto &registry = state.getRegistry();

    registry.view<SpriteComponent>().each([this, &registry](entt::entity entity, SpriteComponent &spriteComponent) {
        sf::RenderStates states;

        TransformComponent *transformComponent = registry.try_get<TransformComponent>(entity);
        if (transformComponent != nullptr)
        {
            states.transform = transformComponent->transform;
        }

        m_renderingQueue->push(spriteComponent.layer,
                               RenderingQueue::Item{spriteComponent.order, &spriteComponent.rectangleShape, states});
    });
}

}  // namespace game
