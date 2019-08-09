#pragma once

#include "Game/Scenes/MainScene.hpp"
#include "Game/Stuff/System.hpp"

namespace game
{
class CarMovementSystem final : public System<MainSceneState>
{
public:
    explicit CarMovementSystem(MainSceneState &state);

    void update(MainSceneState &state, double dt) override;
};


struct CarComponent
{
};

}  // namespace game
