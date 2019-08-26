#pragma once

#include <entt/entity/helper.hpp>
#include <glm/mat3x3.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <Core/Rendering/Texture.hpp>

namespace game
{
// Tags
//

using MainCameraTag = entt::tag<"main_camera"_hs>;

using WindowResizeableCameraTag = entt::tag<"window_resizeable_camera"_hs>;

// Components
//

struct TransformComponent
{
    glm::vec2 position{0.0f, 0.0f};
    float rotation{0.0f};
    glm::vec2 scale{1.0f, 1.0f};
};


struct CameraComponent
{
    float zoom{1.0f};
    glm::mat3 projection{1.0f};
};


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


struct SpriteComponent
{
    RenderingLayer layer{RenderingLayer::GROUND};
    int8_t order{0};

    glm::vec2 size{0.0f, 0.0f};
    glm::vec4 color{1.0f, 1.0f, 1.0f, 1.0f};
    const core::Texture *texture{nullptr};
};

}  // namespace game
