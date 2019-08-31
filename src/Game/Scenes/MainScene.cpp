// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "MainScene.hpp"

#include <glm/gtx/matrix_transform_2d.hpp>

#include <Core/Resources/TextureLoader.hpp>

#include "Game/Components/Car.hpp"
#include "Game/Components/General.hpp"
#include "Game/Stuff/Scene.hpp"
#include "Game/Systems/CameraMovementSystem.hpp"
#include "Game/Systems/CameraResizingSystem.hpp"
#include "Game/Systems/CarMovementSystem.hpp"
#include "Game/Systems/InputSystem.hpp"
#include "Game/Systems/RenderingSystem.hpp"
#include "Game/Systems/SpriteRenderingSystem.hpp"
#include "Game/Systems/WheelsPositioningSystem.hpp"

using namespace core;

namespace game
{
MainSceneState::MainSceneState(Core &core, entt::registry &registry, entt::dispatcher &dispatcher)
    : SharedState(core, registry, dispatcher)
{
    core.get<WindowManager>().lock()->setVsyncEnabled(true);
}


void createMap(MainSceneState &state)
{
    constexpr auto TILE_SIZE = glm::uvec2{512, 512};
    constexpr auto MAP_SIZE = glm::uvec2{9, 5};

    constexpr auto OFFSET = glm::vec2{TILE_SIZE} * glm::vec2{MAP_SIZE} * 0.5f;

    auto &registry = state.getRegistry();

    for (auto y = 0u; y < MAP_SIZE.y; ++y)
    {
        for (auto x = 0u; x < MAP_SIZE.x; ++x)
        {
            const auto textureName = "map/map_" + std::to_string(y) + "_" + std::to_string(x);

            const auto texture = state.getResourcesScope()
                                     .get<Texture>(textureName, TextureLoader{state.getCore(), textureName + ".png"})
                                     .lock();

            const auto transform = TransformComponent{
                glm::translate(glm::mat3{1.0f}, glm::vec2{TILE_SIZE} * glm::vec2{x, MAP_SIZE.y - y - 1} - OFFSET)};

            const auto sprite = SpriteComponent{
                RenderingLayer::GROUND,  // rendering layer
                1,                       // order in layer
                TILE_SIZE,               // size
                glm::vec4{1.0f},         // color
                texture.get()            // texture
            };

            auto entity = registry.create();
            registry.assign<TransformComponent>(entity, transform);
            registry.assign<SpriteComponent>(entity, sprite);
        }
    }
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


entt::entity createWheel(MainSceneState &state)
{
    auto &registry = state.getRegistry();

    const auto wheel = WheelComponent{
        0.45f * 20.0f,  // diameter
        0.2f * 20.0f,   // width
    };

    const auto sprite = SpriteComponent{
        RenderingLayer::CAR,                      // rendering layer
        1,                                        // order in layer
        glm::uvec2{wheel.width, wheel.diameter},  // size
        glm::vec4{1.0f, 0.0f, 0.0f, 1.0f},        // color
        nullptr                                   // texture
    };

    auto entity = registry.create();
    registry.assign<TransformComponent>(entity);
    registry.assign<SpriteComponent>(entity, sprite);
    registry.assign<WheelComponent>(entity, wheel);

    return entity;
}


entt::entity createCar(MainSceneState &state)
{
    auto &registry = state.getRegistry();

    const auto texture =
        state.getResourcesScope().get<Texture>("car_texture", TextureLoader{state.getCore(), "car.png"}).lock();

    const auto car = CarComponent{
        createWheel(state),  // front left wheel
        createWheel(state),  // front right wheel
        createWheel(state),  // rear left wheel
        createWheel(state),  // rear right wheel

        4.445f * 20.0f,  // length
        1.695f * 20.0f,  // width
        1.285f * 20.0f,  // height

        2.525f * 20.0f,  // wheelbase length
        1.470f * 20.0f,  // front track width
        1.460f * 20.0f,  // rear track width
    };

    const auto sprite = SpriteComponent{
        RenderingLayer::CAR,                // rendering layer
        0,                                  // order in layer
        texture->getSize(),                 // size
        glm::vec4{1.0f, 1.0f, 1.0f, 1.0f},  // color
        texture.get()                       // texture
    };

    auto entity = registry.create();
    registry.assign<PlayerTag>(entity);
    registry.assign<TransformComponent>(entity);
    registry.assign<CarComponent>(entity, car);
    registry.assign<SpriteComponent>(entity, sprite);

    return entity;
}


std::unique_ptr<core::Scene> createMainScene(Core &core)
{
    using SceneSystems = Systems<InputSystem, CameraResizingSystem, CarMovementSystem, WheelsPositioningSystem,
                                 CameraMovementSystem, SpriteRenderingSystem, RenderingSystem>;

    auto scene = std::make_unique<Scene<MainSceneState, SceneSystems>>(core);

    auto &state = scene->getState();
    auto &registry = state.getRegistry();

    createMap(state);
    const auto camera = createMainCamera(state);
    const auto car = createCar(state);

    const auto cameraJoint = CameraJointComponent{
        car,  // target
        0.5f  // factor
    };
    registry.assign<CameraJointComponent>(camera, cameraJoint);

    return scene;
}  // namespace game

}  // namespace game
