#pragma once

#include <Core/Managers/WindowManager.hpp>
#include <Core/Rendering/RenderingQueue.hpp>

#include "System.hpp"

namespace game
{
class RenderingSystem final : public System
{
public:
    explicit RenderingSystem(core::Core &core);

private:
    void update(entt::registry &registry, double dt) override;

    std::shared_ptr<core::WindowManager> m_windowManager;

    std::shared_ptr<core::RenderingQueue> m_renderingQueue;
};

}  // namespace game
