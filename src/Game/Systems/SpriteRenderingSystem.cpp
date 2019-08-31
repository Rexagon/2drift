// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "SpriteRenderingSystem.hpp"

#include <glm/gtx/matrix_transform_2d.hpp>

#include <Core/Core.hpp>
#include <Core/Rendering/Stuff/MeshGeometry.hpp>

#include "Game/Components/General.hpp"

using namespace core;

namespace
{
bool contains(const glm::vec2 &boxOffset, glm::vec2 boxSize, const glm::mat3 &transform, glm::vec2 size)
{
    boxSize *= 0.5f;
    size *= 0.5f;

    const auto right = glm::vec2{transform[0][0], transform[0][1]};
    const auto up = glm::vec2{transform[1][0], transform[1][1]};

    const auto xa = right * -size.x;
    const auto xb = right * size.x;

    const auto ya = up * -size.y;
    const auto yb = up * size.y;

    const auto translation = glm::vec2{transform[2][0], transform[2][1]};
    size = (glm::abs(xa - xb) + glm::abs(ya - yb)) * 0.5f;

    const auto interLeft = std::max(boxOffset.x - boxSize.x, translation.x - size.x);
    const auto interBottom = std::max(boxOffset.y - boxSize.y, translation.y - size.y);
    const auto interRight = std::min(boxOffset.x + boxSize.x, translation.x + size.x);
    const auto interTop = std::min(boxOffset.y + boxSize.y, translation.y + size.y);

    return (interLeft < interRight) && (interBottom < interTop);
}

}  // namespace


namespace game
{
SpriteRenderingSystem::SpriteRenderingSystem(SharedState &state)
    : System{state}
    , m_windowManager{state.getCore().get<WindowManager>().lock()}
    , m_material{state.getCore(), state.getResourcesScope()}
    , m_spriteMesh{}
{
    m_spriteMesh.update(MeshGeometry::createRectangle(glm::vec2{-0.5f, 0.5f}, glm::vec2{0.5f, -0.5f}));
}


void SpriteRenderingSystem::update(game::SharedState &state, float /*dt*/)
{
    auto &registry = state.getRegistry();

    const auto &windowSize = m_windowManager->getSize();

    // Find main camera
    const auto &[cameraParameters, cameraTransform] =
        registry.get<CameraComponent, TransformComponent>(*registry.view<MainCameraTag>().begin());

    m_material.setCameraMatrix(cameraParameters.projection * cameraTransform.transform);

    const auto cameraOffset = -glm::vec2{cameraTransform.transform[2]};

    registry.view<SpriteComponent>().each([&, this](entt::entity entity, SpriteComponent &spriteComponent) {
        const auto *t = registry.try_get<TransformComponent>(entity);

        if (t != nullptr && !contains(cameraOffset, glm::vec2{windowSize}, t->transform, spriteComponent.size))
        {
            return;
        }

        auto parameters = std::make_unique<SpriteMaterial::Parameters>();

        parameters->setSize(spriteComponent.size);
        parameters->setColor(spriteComponent.color);
        parameters->setTexture(spriteComponent.texture);

        if (t != nullptr)
        {
            parameters->setTransformation(t->transform);
        }

        state.getRenderingQueue().push(spriteComponent.layer, RenderingQueue::Item{spriteComponent.order, &m_spriteMesh,
                                                                                   &m_material, std::move(parameters)});
    });
}

}  // namespace game
