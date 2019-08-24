// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "MainScene.hpp"

#include "Game/Stuff/Scene.hpp"
#include "Game/Systems/CameraResizingSystem.hpp"
#include "Game/Systems/CarMovementSystem.hpp"
#include "Game/Systems/InputSystem.hpp"
#include "Game/Systems/RenderingSystem.hpp"
#include "Game/Systems/SpriteRenderingSystem.hpp"

struct Comp1
{
    float a = 0.0f;
};

struct Comp2
{
    float b = 0.0f;
};

namespace game
{
MainSceneState::MainSceneState(core::Core &core, entt::registry &registry, entt::dispatcher &dispatcher)
    : SharedState(core, registry, dispatcher)
{
}

std::unique_ptr<core::Scene> createMainScene(core::Core &core)
{
    using SceneSystems =
        Systems<InputSystem, CameraResizingSystem, CarMovementSystem, SpriteRenderingSystem, RenderingSystem>;

    auto scene = std::make_unique<Scene<MainSceneState, SceneSystems>>(core);

    auto &state = scene->getState();
    auto &registry = state.getRegistry();

    // Create camera
    auto cameraEntity = registry.create();
    registry.assign<MainCamera>(cameraEntity);
    registry.assign<TransformComponent>(cameraEntity);
    registry.assign<WindowResizeableComponent>(cameraEntity);
    registry.assign<CameraComponent>(cameraEntity, CameraComponent{});

    // Create car
    auto spriteEntity = registry.create();
    registry.assign<TransformComponent>(spriteEntity);
    registry.assign<CarComponent>(spriteEntity);
    registry.assign<SpriteComponent>(spriteEntity,
                                     SpriteComponent{RenderingLayer::GROUND, 0, glm::vec2{40.0f, 100.0f}});

    return scene;
}  // namespace game

}  // namespace game
