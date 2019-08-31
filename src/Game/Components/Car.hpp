#pragma once

#include <entt/entity/entity.hpp>
#include <glm/vec2.hpp>

namespace game
{
// Car specific components
//

struct CarComponent
{
    entt::entity frontLeftWheel{};
    entt::entity frontRightWheel{};
    entt::entity rearLeftWheel{};
    entt::entity rearRightWheel{};

    float maxSteeringAngle{};

    float length{};
    float width{};
    float height{};

    float wheelbaseLength{};
    float frontTrackWidth{};
    float rearTrackWidth{};

    glm::vec2 spriteOffset{0.0f, 0.0f};
};


struct CarControlsComponent
{
    float steering{};

    float throttle{};
    float breaks{};
    float clutch{};
    float handbrake{};
};


struct WheelComponent
{
    float diameter{0.0f};
    float width{0.0f};

    float chamber{0.0f};
    float toe{0.0f};
};


struct SteeringWheelComponent
{
    float caster{0.0f};
    float angle{0.0f};
};

}  // namespace game
