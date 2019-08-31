// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "CarMovementSystem.hpp"

#include <glm/gtx/matrix_transform_2d.hpp>

#include "Game/Components/Car.hpp"
#include "Game/Components/General.hpp"

using namespace core;

namespace game
{
CarMovementSystem::CarMovementSystem(MainSceneState &state)
    : System{state}
{
}


void CarMovementSystem::update(MainSceneState &state, float dt)
{
    auto &registry = state.getRegistry();

    auto carEntities = registry.view<TransformComponent, CarComponent, CarControlsComponent>();
    carEntities.each([&](TransformComponent &transform, const CarComponent &car, const CarControlsComponent &controls) {
        // Set front left wheel steering
        auto &frontLeftWheel = registry.get<SteeringWheelComponent>(car.frontLeftWheel);
        frontLeftWheel.angle = controls.steering * car.maxSteeringAngle;

        // Set front right wheel steering
        auto &frontRightWheel = registry.get<SteeringWheelComponent>(car.frontRightWheel);
        frontRightWheel.angle = controls.steering * car.maxSteeringAngle;


        const auto translation = glm::translate(glm::mat3{1.0f}, glm::vec2{0.0f, 100.0f * controls.throttle * dt});
        const auto rotation = glm::rotate(glm::mat3{1.0f}, controls.steering * dt);

        transform.matrix *= rotation * translation;
    });
}


}  // namespace game
