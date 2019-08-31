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
            auto *t = registry.try_get<TransformComponent>(entity);
            if (t == nullptr)
            {
                return;
            }

            auto *target = registry.try_get<TransformComponent>(joint.target);
            if (target == nullptr)
            {
                return;
            }

            const auto position = -glm::vec2{t->transform[2]};
            const auto targetPosition = glm::vec2{target->transform[2]};

            t->transform = glm::translate(t->transform, -(targetPosition - position) * joint.factor * dt);
        });
}

}  // namespace game
