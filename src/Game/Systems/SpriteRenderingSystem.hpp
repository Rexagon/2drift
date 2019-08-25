#pragma once

#include <Core/Managers/WindowManager.hpp>
#include <Core/Rendering/Mesh.hpp>
#include <Core/Rendering/Texture.hpp>

#include "Game/Rendering/SpriteMaterial.hpp"
#include "Game/Stuff/System.hpp"
#include "General.hpp"

namespace game
{
class SpriteRenderingSystem : public System<SharedState>
{
public:
    explicit SpriteRenderingSystem(SharedState &state);

    void update(SharedState &state, float dt) override;

private:
    std::shared_ptr<core::WindowManager> m_windowManager;

    SpriteMaterial m_material;

    core::Mesh m_spriteMesh;
};


struct SpriteComponent
{
    RenderingLayer layer{RenderingLayer::GROUND};
    int8_t order{0};

    glm::vec2 size{0.0f, 0.0f};
    const core::Texture *texture{nullptr};
};

}  // namespace game
