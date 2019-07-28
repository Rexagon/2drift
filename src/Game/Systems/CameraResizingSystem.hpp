#pragma once

#include <Core/Managers/WindowManager.hpp>

#include "Game/Stuff/System.hpp"

namespace game
{
class CameraResizingSystem : public System
{
public:
    explicit CameraResizingSystem(core::Core &core);

    void update(SharedState &state, double dt);

private:
    std::shared_ptr<core::WindowManager> m_windowManager;
};

struct WindowResizeableComponent
{
};

}  // namespace game
