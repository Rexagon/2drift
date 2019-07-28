#pragma once

#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/View.hpp>
#include <entt/entity/helper.hpp>

namespace game
{
// Components

struct TransformComponent
{
    sf::Transform transform;
};


struct CameraComponent
{
    sf::View view;
};


// Constants
constexpr auto RENDERING_QUEUE = "rendering_queue";

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
