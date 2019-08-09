#pragma once

#include <Core/Managers/WindowManager.hpp>
#include <Core/Rendering/RenderingQueue.hpp>

#include "Game/Stuff/System.hpp"

namespace game
{
class RenderingSystem final : public System<SharedState>
{
public:
    explicit RenderingSystem(SharedState &state);

    void update(SharedState &state, double dt) override;

private:
    std::shared_ptr<core::WindowManager> m_windowManager;
};

}  // namespace game
