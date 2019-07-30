#pragma once

#include <Core/Managers/WindowManager.hpp>

#include "Game/Stuff/System.hpp"

namespace game
{
class CameraResizingSystem : public System<SharedState>
{
public:
    explicit CameraResizingSystem(SharedState &core);

    void operator()(SharedState &state, double dt) override;

private:
    void handleEvent(const sf::Event &e);

    bool m_isWindowSizeChanged = true;

    std::shared_ptr<core::WindowManager> m_windowManager;
};

struct WindowResizeableComponent
{
};

}  // namespace game
