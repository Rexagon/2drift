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

    view.each([&registry](const CarComponent &car, const TransformComponent &t) {
        const auto &offset = car.spriteOffset;
        const auto halfWheelbase = glm::vec2{0.0f, car.wheelbaseLength * 0.5f};
        const auto frontTrackCenter = offset + halfWheelbase;
        const auto rearTrackCenter = offset - halfWheelbase;

        // Front left
        auto &frontLeftWheel = registry.get<TransformComponent>(car.frontLeftWheel);
        const auto frontLeftPosition = frontTrackCenter - glm::vec2{car.frontTrackWidth * 0.5f, 0.0f};
        frontLeftWheel.transform = glm::translate(t.transform, frontLeftPosition);

        // Front right
        auto &frontRightWheel = registry.get<TransformComponent>(car.frontRightWheel);
        const auto frontRightPosition = frontTrackCenter + glm::vec2{car.frontTrackWidth * 0.5f, 0.0f};
        frontRightWheel.transform = glm::translate(t.transform, frontRightPosition);

        // Rear left
        auto &rearLeftWheel = registry.get<TransformComponent>(car.rearLeftWheel);
        const auto rearLeftPosition = rearTrackCenter - glm::vec2{car.rearTrackWidth * 0.5f, 0.0f};
        rearLeftWheel.transform = glm::translate(t.transform, rearLeftPosition);

        // Rear right
        auto &rearRightWheel = registry.get<TransformComponent>(car.rearRightWheel);
        const auto rearRightPosition = rearTrackCenter + glm::vec2{car.rearTrackWidth * 0.5f, 0.0f};
        rearRightWheel.transform = glm::translate(t.transform, rearRightPosition);
    });
}

}  // namespace game
