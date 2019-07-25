#pragma once

#include <Core/Managers/SceneManager.hpp>

namespace game
{
class MainScene final : public core::Scene
{
public:
    explicit MainScene(core::Core &core);

    void onUpdate(double dt) override;

private:
};

}  // namespace game
