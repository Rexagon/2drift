#pragma once

#include "Game/Scenes/MainScene.hpp"
#include "Game/Stuff/System.hpp"

namespace game
{
class CarMovementSystem final : public System<MainSceneState>
{
public:
    explicit CarMovementSystem(MainSceneState &state);

    void update(MainSceneState &state, float dt) override;
};


struct CarComponent
{
};

}  // namespace game
