#pragma once

#include <entt/entity/helper.hpp>

namespace game
{
// Components

struct TransformComponent
{
    glm::vec2 position{0.0f, 0.0f};
    float rotation = 0.0f;
    glm::vec2 scale{1.0f, 1.0f};
};


struct CameraComponent
{
    float zoom = 1.0f;
    glm::mat3 projection;
};


// Constants
using MainCamera = entt::tag<"main_camera"_hs>;

enum RenderingLayer : uint8_t
{
    GROUND,
    GROUND_DETAILS,
    WHEELS,
    CAR,
    SMOKE,
    TREES,
    BUILDINGS,

    UI
};

}  // namespace game
