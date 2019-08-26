// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "WheelsPositioningSystem.hpp"

#include <glm/gtx/rotate_vector.hpp>

#include "Game/Components/Car.hpp"
#include "Game/Components/General.hpp"

namespace game
{
WheelsPositioningSystem::WheelsPositioningSystem(MainSceneState &state)
    : System{state}
{
}


void WheelsPositioningSystem::update(MainSceneState &state, float /* dt */)
{
    auto &registry = state.getRegistry();

    const auto view = registry.view<CarComponent, TransformComponent>();

    view.each([&registry](const CarComponent &car, const TransformComponent &transform) {
        const auto front = glm::rotate(glm::vec2{0.0f, 1.0f}, transform.rotation);
        const auto right = glm::vec2{front.y, -front.x};

        const auto &offset = car.spriteOffset;

        const auto halfWheelbase = glm::vec2{0.0f, car.wheelbaseLength * 0.5f};

        const auto frontTrackCenter = offset + halfWheelbase;
        const auto frontLeftPosition = frontTrackCenter - glm::vec2{car.frontTrackWidth * 0.5f, 0.0f};
        const auto frontRightPosition = frontTrackCenter + glm::vec2{car.frontTrackWidth * 0.5f, 0.0f};

        auto &flWheelTransform = registry.get<TransformComponent>(car.frontLeftWheel);
        flWheelTransform.position = transform.position + frontLeftPosition.x * right + frontLeftPosition.y * front;
        flWheelTransform.rotation = transform.rotation;

        auto &frWheelTransform = registry.get<TransformComponent>(car.frontRightWheel);
        frWheelTransform.position = transform.position + frontRightPosition.x * right + frontRightPosition.y * front;
        frWheelTransform.rotation = transform.rotation;

        const auto rearTrackCenter = offset - halfWheelbase;
        const auto rearLeftPosition = rearTrackCenter - glm::vec2{car.rearTrackWidth * 0.5f, 0.0f};
        const auto rearRightPosition = rearTrackCenter + glm::vec2{car.rearTrackWidth * 0.5f, 0.0f};

        auto &rlWheelTransform = registry.get<TransformComponent>(car.rearLeftWheel);
        rlWheelTransform.position = transform.position + rearLeftPosition.x * right + rearLeftPosition.y * front;
        rlWheelTransform.rotation = transform.rotation;

        auto &rrWheelTransform = registry.get<TransformComponent>(car.rearRightWheel);
        rrWheelTransform.position = transform.position + rearRightPosition.x * right + rearRightPosition.y * front;
        rrWheelTransform.rotation = transform.rotation;
    });
}

}  // namespace game
