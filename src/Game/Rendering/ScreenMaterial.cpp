// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ScreenMaterial.hpp"

#include <Core/Core.hpp>
#include <Core/Resources/ShaderLoader.hpp>

using namespace core;

namespace
{
constexpr const auto SCREEN_SHADER_NAME = "screen_shader";
constexpr const auto SCREEN_VERTEX_SHADER = "screen.vert";
constexpr const auto SCREEN_FRAGMENT_SHADER = "screen.frag";

constexpr const auto RENDERING_PARAMETERS = RenderingParameters{
    false /* is depth test enabled */,
    false /* is depth write enabled */,
    GL_LEQUAL /* depth test function */,

    false /* is blending enabled */,
    GL_SRC_ALPHA /* blending function src */,
    GL_ONE_MINUS_SRC_ALPHA /* blending function dst */,

    true /* is face culling enabled */,
    GL_BACK /* face culling side */,

    GL_FILL /* polygon mode */,
};
}  // namespace

namespace game
{
ScreenMaterial::ScreenMaterial(Core &core)
    : Material{core, RENDERING_PARAMETERS, nullptr}
    , m_resourcesScope{core}
{
    m_resourcesScope.bind<Shader>(SCREEN_SHADER_NAME, ShaderLoader{core, SCREEN_VERTEX_SHADER, SCREEN_FRAGMENT_SHADER});

    auto resourceManager = core.get<ResourceManager>().lock();
    setShader(resourceManager->get<Shader>(SCREEN_SHADER_NAME).lock());

    getShader().bind();
    getShader().setUniform("uScreenTexture", SCREEN_TEXTURE_SLOT);
}

}  // namespace game
