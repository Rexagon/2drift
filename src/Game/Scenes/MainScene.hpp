#pragma once

#include <Core/Managers/SceneManager.hpp>

namespace game
{
std::unique_ptr<core::Scene> createMainScene(core::Core &core);

}  // namespace game
