#pragma once

#include <Core/Managers/InputManager.hpp>

#include "Game/Scenes/MainScene.hpp"
#include "Game/Stuff/System.hpp"

namespace game
{
class InputSystem final : public System<MainSceneState>
{
public:
    explicit InputSystem(MainSceneState &state);

    void update(MainSceneState &state, float dt) override;

private:
    void updateHalfAxis(float &axis, core::keyboard::Key key, float dt, float speed, float min = 0.0, float max = 1.0);

    void updateFullAxis(float &axis,
                        core::keyboard::Key upKey,
                        core::keyboard::Key downKey,
                        float dt,
                        float speed,
                        float min = -1.0,
                        float max = 1.0);

    std::shared_ptr<core::InputManager> m_inputManager;
};

}  // namespace game
