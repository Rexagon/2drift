// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "CarMovementSystem.hpp"

#include <glm/gtx/matrix_transform_2d.hpp>

#include "Game/Components/Car.hpp"
#include "Game/Components/General.hpp"

using namespace core;

namespace game
{
CarMovementSystem::CarMovementSystem(MainSceneState &state)
    : System{state}
{
}


void CarMovementSystem::update(MainSceneState &state, float dt)
{
    auto &registry = state.getRegistry();

    const auto &input = state.getInput();

    auto carEntities = registry.view<TransformComponent, CarComponent>();
    carEntities.each([&](TransformComponent &t, const CarComponent &) {
        const auto translation = glm::translate(glm::mat3{1.0f}, glm::vec2{0.0f, 100.0f * input.throttleAxis * dt});
        const auto rotation = glm::rotate(glm::mat3{1.0f}, input.steeringAxis * dt);

        t.transform *= rotation * translation;
    });
}


}  // namespace game
