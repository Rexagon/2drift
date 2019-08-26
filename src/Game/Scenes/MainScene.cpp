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
{
}


entt::entity createMainCamera(MainSceneState &state)
{
    auto &registry = state.getRegistry();

    auto entity = registry.create();
    registry.assign<MainCameraTag>(entity);
    registry.assign<WindowResizeableCameraTag>(entity);
    registry.assign<TransformComponent>(entity);
    registry.assign<CameraComponent>(entity);

    return entity;
}


entt::entity createCar(MainSceneState &state)
{
    auto &registry = state.getRegistry();

    const auto texture =
        state.getResourcesScope().get<Texture>("car_texture", TextureLoader{state.getCore(), "car.png"}).lock();

    const auto sprite = SpriteComponent{
        RenderingLayer::CAR,                // rendering layer
        0,                                  // order in layer
        texture->getSize(),                 // size
        glm::vec4{1.0f, 1.0f, 1.0f, 1.0f},  // color
        texture.get()                       // texture
    };

    auto entity = registry.create();
    registry.assign<TransformComponent>(entity);
    registry.assign<CarComponent>(entity);
    registry.assign<SpriteComponent>(entity, sprite);

    return entity;
}


std::unique_ptr<core::Scene> createMainScene(Core &core)
{
    using SceneSystems =
        Systems<InputSystem, CameraResizingSystem, CarMovementSystem, SpriteRenderingSystem, RenderingSystem>;

    auto scene = std::make_unique<Scene<MainSceneState, SceneSystems>>(core);

    auto &state = scene->getState();

    createMainCamera(state);
    createCar(state);

    return scene;
}  // namespace game

}  // namespace game
