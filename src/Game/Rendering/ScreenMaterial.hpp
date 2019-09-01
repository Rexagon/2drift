#pragma once

#include <Core/Rendering/Material.hpp>
#include <Core/Rendering/Stuff/ShaderParameters.hpp>
#include <Core/Resources/Stuff/ResourcesScope.hpp>

namespace game
{
class ScreenMaterial final : public core::Material
{
public:
    explicit ScreenMaterial(core::Core &core, core::ResourcesScope &resourcesScope);

    constexpr static auto SCREEN_TEXTURE_SLOT = 10;
};

}  // namespace game
