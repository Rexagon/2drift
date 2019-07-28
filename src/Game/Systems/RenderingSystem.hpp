#pragma once

#include <Core/Managers/WindowManager.hpp>
#include <Core/Rendering/RenderingQueue.hpp>

#include "Game/Stuff/System.hpp"

namespace game
{
class RenderingSystem final : public System
{
public:
    explicit RenderingSystem(core::Core &core);

    void update(SharedState &state, double dt);

private:

    std::shared_ptr<core::WindowManager> m_windowManager;
};

}  // namespace game
