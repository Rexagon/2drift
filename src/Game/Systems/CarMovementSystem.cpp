// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "CarMovementSystem.hpp"

#include "General.hpp"

using namespace core;

namespace game
{
CarMovementSystem::CarMovementSystem(MainSceneState &state)
    : System{state}
{
}


void CarMovementSystem::update(MainSceneState &state, double dt)
{
    auto &registry = state.getRegistry();

    const auto &input = state.getInput();

    auto carEntities = registry.view<TransformComponent, CarComponent>();
    carEntities.each([&](TransformComponent &transformComponent, const CarComponent &) {
        sf::Transform transform;
        transform.translate(0.0f, -static_cast<float>(100.0f * input.throttleAxis * dt));
        transform.rotate(-static_cast<float>(input.steeringAxis));

        transformComponent.transform.combine(transform);
    });
}


}  // namespace game
