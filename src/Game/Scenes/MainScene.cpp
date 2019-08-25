// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "MainScene.hpp"

#include <Core/Resources/TextureLoader.hpp>

#include "Game/Stuff/Scene.hpp"
#include "Game/Systems/CameraResizingSystem.hpp"
#include "Game/Systems/CarMovementSystem.hpp"
#include "Game/Systems/InputSystem.hpp"
#include "Game/Systems/RenderingSystem.hpp"
#include "Game/Systems/SpriteRenderingSystem.hpp"

using namespace core;

namespace game
{
MainSceneState::MainSceneState(Core &core, entt::registry &registry, entt::dispatcher &dispatcher)
    : SharedState(core, registry, dispatcher)
    , m_resourcesScope{core}
{
}


std::unique_ptr<core::Scene> createMainScene(core::Core &core)
{
    using SceneSystems =
        Systems<InputSystem, CameraResizingSystem, CarMovementSystem, SpriteRenderingSystem, RenderingSystem>;

    auto scene = std::make_unique<Scene<MainSceneState, SceneSystems>>(core);

    auto &state = scene->getState();
    auto &registry = state.getRegistry();
    auto &resourcesScope = state.getResourcesScope();

    resourcesScope.bind<Texture>("car_texture", TextureLoader{core, "car.png"});

    // Create camera
    auto cameraEntity = registry.create();
    registry.assign<MainCameraTag>(cameraEntity);
    registry.assign<WindowResizeableCameraTag>(cameraEntity);
    registry.assign<TransformComponent>(cameraEntity);
    registry.assign<CameraComponent>(cameraEntity);

    // Create car
    auto carTexture = core.get<ResourceManager>().lock()->get<Texture>("car_texture").lock();

    auto spriteEntity = registry.create();
    registry.assign<TransformComponent>(spriteEntity);
    registry.assign<CarComponent>(spriteEntity);
    registry.assign<SpriteComponent>(
        spriteEntity, SpriteComponent{RenderingLayer::GROUND, 0, glm::vec2{34.0f, 89.0f}, carTexture.get()});

    return scene;
}  // namespace game

}  // namespace game
