#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include <Core/Rendering/RenderingQueue.hpp>

#include "Game/Stuff/System.hpp"
#include "General.hpp"

namespace game
{
class SpriteRenderingSystem : public System
{
public:
    explicit SpriteRenderingSystem(core::Core &core);

    void update(SharedState &state, double dt) override;

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
