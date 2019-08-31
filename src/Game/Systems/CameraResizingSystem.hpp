#pragma once

#include <Core/Managers/WindowManager.hpp>

#include "Game/Stuff/System.hpp"

namespace game
{
class CameraResizingSystem : public System<SharedState>
{
public:
    explicit CameraResizingSystem(SharedState &core);

    void update(SharedState &state, float dt) override;

private:
    void handleEvent(const core::Event &e);

    bool m_isWindowSizeChanged = true;

    std::shared_ptr<core::WindowManager> m_windowManager;
};

}  // namespace game
