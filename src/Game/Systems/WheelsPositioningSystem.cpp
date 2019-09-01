// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "WheelsPositioningSystem.hpp"

#include <glm/gtx/matrix_transform_2d.hpp>

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

    view.each([&registry](const CarComponent &car, const TransformComponent &carTransform) {
        const auto &offset = car.spriteOffset;
        const auto halfWheelbase = glm::vec2{0.0f, car.wheelbaseLength * 0.5f};
        const auto frontTrackCenter = offset + halfWheelbase;
        const auto rearTrackCenter = offset - halfWheelbase;

        // Front left
        const auto frontLeftPosition = frontTrackCenter - glm::vec2{car.frontTrackWidth * 0.5f, 0.0f};

        auto [frontLeftWheelTransform, frontLeftWheel, frontLeftWheelSteering] =
            registry.get<TransformComponent, WheelComponent, SteeringWheelComponent>(car.frontLeftWheel);

        frontLeftWheelTransform.matrix = glm::rotate(glm::translate(carTransform.matrix, frontLeftPosition),
                                                     frontLeftWheelSteering.angle + frontLeftWheel.toe);

        // Front right
        const auto frontRightPosition = frontTrackCenter + glm::vec2{car.frontTrackWidth * 0.5f, 0.0f};

        auto [frontRightWheelTransform, frontRightWheel, frontRightWheelSteering] =
            registry.get<TransformComponent, WheelComponent, SteeringWheelComponent>(car.frontRightWheel);

        frontRightWheelTransform.matrix = glm::rotate(glm::translate(carTransform.matrix, frontRightPosition),
                                                      frontRightWheelSteering.angle - frontRightWheel.toe);

        // Rear left
        const auto rearLeftPosition = rearTrackCenter - glm::vec2{car.rearTrackWidth * 0.5f, 0.0f};

        auto [rearLeftWheelTransform, rearLeftWheel] =
            registry.get<TransformComponent, WheelComponent>(car.rearLeftWheel);

        rearLeftWheelTransform.matrix =
            glm::rotate(glm::translate(carTransform.matrix, rearLeftPosition), rearLeftWheel.toe);

        // Rear right
        const auto rearRightPosition = rearTrackCenter + glm::vec2{car.rearTrackWidth * 0.5f, 0.0f};

        auto [rearRightWheelTransform, rearRightWheel] =
            registry.get<TransformComponent, WheelComponent>(car.rearRightWheel);

        rearRightWheelTransform.matrix =
            glm::rotate(glm::translate(carTransform.matrix, rearRightPosition), -rearRightWheel.toe);
    });
}

}  // namespace game
