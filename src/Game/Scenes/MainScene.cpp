// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "MainScene.hpp"

#include "Game/Stuff/Scene.hpp"
#include "Game/Systems/CameraResizingSystem.hpp"
#include "Game/Systems/RenderingSystem.hpp"
#include "Game/Systems/SpriteRenderingSystem.hpp"

namespace game
{
std::unique_ptr<core::Scene> createMainScene(core::Core &core)
{
    using SceneSystems = Systems<CameraResizingSystem, SpriteRenderingSystem, RenderingSystem>;

    auto scene = std::make_unique<Scene<SharedState, SceneSystems>>(core);

    auto &state = scene->getState();

    state.getRegistry().create<MainCamera, TransformComponent, CameraComponent, WindowResizeableComponent>();

    auto spriteEntity = state.getRegistry().create();
    state.getRegistry().assign<SpriteComponent>(
        spriteEntity, SpriteComponent{RenderingLayer::GROUND, 0, sf::RectangleShape{sf::Vector2f{100.0f, 100.0f}}});


    return scene;
}

}  // namespace game
