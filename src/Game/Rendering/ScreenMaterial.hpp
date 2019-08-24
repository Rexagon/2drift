#pragma once

#include <Core/Rendering/Material.hpp>
#include <Core/Rendering/Stuff/ShaderParameters.hpp>
#include <Core/Resources/Stuff/ResourcesScope.hpp>

namespace game
{
class ScreenMaterial final : public core::Material
{
public:
    explicit ScreenMaterial(core::Core &core);

    constexpr static auto SCREEN_TEXTURE_SLOT = 10;

private:
    core::ResourcesScope m_resourcesScope;
};

}  // namespace game
