#pragma once

#include "Game/Stuff/System.hpp"

namespace game
{
class CameraMovementSystem final : public System<SharedState>
{
public:
    explicit CameraMovementSystem(SharedState &state);

    void update(SharedState &state, float dt) override;
};

}  // namespace game
