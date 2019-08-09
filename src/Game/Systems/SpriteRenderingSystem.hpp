#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include <Core/Rendering/RenderingQueue.hpp>

#include "Game/Stuff/System.hpp"
#include "General.hpp"

namespace game
{
class SpriteRenderingSystem : public System<SharedState>
{
public:
    explicit SpriteRenderingSystem(SharedState &state);

    void update(SharedState &state, double dt) override;
};


struct SpriteComponent
{
    RenderingLayer layer;
    int8_t order;

    sf::RectangleShape rectangleShape;
};

}  // namespace game
