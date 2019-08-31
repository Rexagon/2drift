#pragma once

#include "Game/Scenes/MainSceneState.hpp"
#include "Game/Stuff/System.hpp"

namespace game
{
class WheelsPositioningSystem final : public System<MainSceneState>
{
public:
    explicit WheelsPositioningSystem(MainSceneState &state);

    void update(MainSceneState &state, float dt) override;
};

}  // namespace game
