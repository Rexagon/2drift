#pragma once

#include <Core/Managers/WindowManager.hpp>
#include <Core/Rendering/Mesh.hpp>

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
    RenderingLayer layer;
    int8_t order;

    glm::vec2 size;
};

}  // namespace game
