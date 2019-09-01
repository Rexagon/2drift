// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "CameraMovementSystem.hpp"

#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

#include "Game/Components/General.hpp"

namespace game
{
CameraMovementSystem::CameraMovementSystem(SharedState &state)
    : System(state)
{
}


void CameraMovementSystem::update(SharedState &state, float dt)
{
    auto &registry = state.getRegistry();

    registry.view<CameraJointComponent>().each(
        [&registry, &dt](const entt::entity entity, const CameraJointComponent &joint) {
            auto *cameraTransform = registry.try_get<TransformComponent>(entity);
            if (cameraTransform == nullptr)
            {
                return;
            }

            auto *targetTransform = registry.try_get<TransformComponent>(joint.target);
            if (targetTransform == nullptr)
            {
                return;
            }

            const auto position = -glm::vec2{cameraTransform->matrix[2]};
            const auto targetPosition = glm::vec2{targetTransform->matrix[2]};

            const auto movement = (targetPosition - position) * joint.factor * dt;

            cameraTransform->matrix = glm::translate(cameraTransform->matrix, -movement);
        });
}

}  // namespace game
