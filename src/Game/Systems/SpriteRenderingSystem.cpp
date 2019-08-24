// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "SpriteRenderingSystem.hpp"

#include <glm/gtx/matrix_transform_2d.hpp>

#include <Core/Core.hpp>
#include <Core/Rendering/Stuff/MeshGeometry.hpp>

using namespace core;

namespace game
{
SpriteRenderingSystem::SpriteRenderingSystem(SharedState &state)
    : System{state}
    , m_windowManager{state.getCore().get<WindowManager>().lock()}
    , m_material{state.getCore()}
    , m_spriteMesh{}
{
    m_spriteMesh.update(MeshGeometry::createRectangle(glm::vec2{-10.0f, 10.0f}, glm::vec2{10.0f, -10.0f}));
}


void SpriteRenderingSystem::update(game::SharedState &state, float /*dt*/)
{
    auto &registry = state.getRegistry();

    // Find main camera
    const auto &camera = registry.get<CameraComponent>(*registry.view<MainCamera>().begin());

    m_material.setCameraMatrix(camera.projection);

    registry.view<SpriteComponent>().each([this, &state, &registry](entt::entity entity,
                                                                    SpriteComponent &spriteComponent) {
        auto parameters = std::make_unique<SpriteMaterial::Parameters>();

        const auto *transform = registry.try_get<TransformComponent>(entity);
        if (transform != nullptr)
        {
            parameters->setTransformation(
                glm::rotate(glm::translate(glm::mat3{1.0f}, transform->position), transform->rotation));
        }

        state.getRenderingQueue().push(spriteComponent.layer, RenderingQueue::Item{spriteComponent.order, &m_spriteMesh,
                                                                                   &m_material, std::move(parameters)});
    });
}

}  // namespace game
