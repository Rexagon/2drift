// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "MainScene.hpp"

#include "Game/Stuff/Scene.hpp"
#include "Game/Systems/CameraResizingSystem.hpp"
#include "Game/Systems/CarMovementSystem.hpp"
#include "Game/Systems/InputSystem.hpp"
#include "Game/Systems/RenderingSystem.hpp"
#include "Game/Systems/SpriteRenderingSystem.hpp"

namespace game
{
MainSceneState::MainSceneState(core::Core &core, entt::registry &registry, entt::dispatcher &dispatcher)
    : SharedState(core, registry, dispatcher)
{
}


std::unique_ptr<core::Scene> createMainScene(core::Core &core)
{
    using SceneSystems =
        Systems<InputSystem, CarMovementSystem, CameraResizingSystem, SpriteRenderingSystem, RenderingSystem>;

    auto scene = std::make_unique<Scene<MainSceneState, SceneSystems>>(core);

    auto &state = scene->getState();
    auto &registry = state.getRegistry();

    // Create camera
    sf::View cameraView{};
    cameraView.zoom(0.5f);

    auto cameraEntity = registry.create();
    registry.assign<TransformComponent>(cameraEntity);
    registry.assign<CameraComponent>(cameraEntity, CameraComponent{cameraView});
    registry.assign<WindowResizeableComponent>(cameraEntity);
    registry.assign<MainCamera>(cameraEntity);

    // Create car
    sf::RectangleShape rectangle{sf::Vector2f{40.0f, 100.0f}};
    rectangle.setOrigin(15.0f, 50.0f);

    auto spriteEntity = state.getRegistry().create();
    registry.assign<TransformComponent>(spriteEntity);
    registry.assign<CarComponent>(spriteEntity);
    registry.assign<SpriteComponent>(spriteEntity, SpriteComponent{RenderingLayer::GROUND, 0, rectangle});


    return scene;
}

}  // namespace game
