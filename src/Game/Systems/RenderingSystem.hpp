#pragma once

#include <entt/entity/helper.hpp>

#include <Core/Managers/WindowManager.hpp>
#include <Core/Rendering/FrameBuffer.hpp>
#include <Core/Rendering/Stuff/RenderingQueue.hpp>

#include "Game/Rendering/ScreenMaterial.hpp"
#include "Game/Stuff/System.hpp"

namespace game
{
class RenderingSystem final : public System<SharedState>
{
public:
    explicit RenderingSystem(SharedState &state);

    void update(SharedState &state, float dt) override;

private:
    std::shared_ptr<core::WindowManager> m_windowManager;
    std::shared_ptr<core::RenderingManager> m_renderingManager;

    core::FrameBuffer m_screenBuffer;

    ScreenMaterial m_screenMaterial;
    core::Mesh m_screenQuad;
};

}  // namespace game
