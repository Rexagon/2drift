// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "MainScene.hpp"

#include <Core/Rendering/RenderingQueue.hpp>

#include "Game/Systems/General.hpp"
#include "Game/Systems/RenderingSystem.hpp"
#include "Game/Systems/SpriteRenderingSystem.hpp"

using namespace core;

namespace game
{
game::MainScene::MainScene(core::Core &core)
    : Scene{core}
    , m_resourcesScope{core}
{
    // Bind all resources
    m_resourcesScope.bind<RenderingQueue>(RENDERING_QUEUE, [] { return std::make_shared<RenderingQueue>(); });

    // Create all systems
    auto spriteRenderingSystem = std::make_unique<SpriteRenderingSystem>(core);
    m_systems.emplace_back(std::move(spriteRenderingSystem));

    auto renderingSystem = std::make_unique<RenderingSystem>(core);
    m_systems.emplace_back(std::move(renderingSystem));

    // Create scene
    m_registry.create<MainCamera, TransformComponent, CameraComponent>();

    auto spriteEntity = m_registry.create();
    m_registry.assign<SpriteComponent>(
        spriteEntity, SpriteComponent{RenderingLayer::GROUND, 0, sf::RectangleShape{sf::Vector2f{100.0f, 100.0f}}});
}


void MainScene::onUpdate(double dt)
{
    for (auto &system : m_systems)
    {
        system->update(m_registry, dt);
    }
}

}  // namespace game
