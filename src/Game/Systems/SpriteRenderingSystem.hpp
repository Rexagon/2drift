#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include <Core/Rendering/RenderingQueue.hpp>

#include "General.hpp"
#include "System.hpp"

namespace game
{
class SpriteRenderingSystem : public System
{
public:
    explicit SpriteRenderingSystem(core::Core &core);

    void update(entt::registry &registry, double dt) override;

private:
    std::shared_ptr<core::RenderingQueue> m_renderingQueue;
};


struct SpriteComponent
{
    RenderingLayer layer;
    int8_t order;

    sf::RectangleShape rectangleShape;
};

}  // namespace game
