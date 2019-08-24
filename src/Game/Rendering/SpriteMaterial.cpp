// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "SpriteMaterial.hpp"

#include <Core/Core.hpp>
#include <Core/Resources/ShaderLoader.hpp>

using namespace core;

namespace
{
constexpr const auto SPRITE_SHADER_NAME = "sprite_shader";
constexpr const auto SPRITE_VERTEX_SHADER = "sprite.vert";
constexpr const auto SPRITE_FRAGMENT_SHADER = "sprite.frag";

constexpr const auto RENDERING_PARAMETERS = RenderingParameters{
    false /* is depth test enabled */,
    false /* is depth write enabled */,
    GL_LEQUAL /* depth test function */,

    true /* is blending enabled */,
    GL_SRC_ALPHA /* blending function src */,
    GL_ONE_MINUS_SRC_ALPHA /* blending function dst */,

    true /* is face culling enabled */,
    GL_BACK /* face culling side */,

    GL_FILL /* polygon mode */,
};

}  // namespace

namespace game
{
void SpriteMaterial::Parameters::apply(core::Shader &shader) const
{
    shader.bind();
    shader.setUniform("uTransformationMatrix", m_transformation);
    shader.setUniform("uColor", m_color);
}


void SpriteMaterial::Parameters::setTransformation(const glm::mat3 &transformation)
{
    m_transformation = transformation;
}


void SpriteMaterial::Parameters::setColor(const glm::vec4 &color)
{
    m_color = color;
}


SpriteMaterial::SpriteMaterial(Core &core)
    : Material{core, RENDERING_PARAMETERS, nullptr}
    , m_resourcesScope{core}
{
    m_resourcesScope.bind<Shader>(SPRITE_SHADER_NAME, ShaderLoader{core, SPRITE_VERTEX_SHADER, SPRITE_FRAGMENT_SHADER});

    auto resourceManager = core.get<ResourceManager>().lock();
    setShader(resourceManager->get<Shader>(SPRITE_SHADER_NAME).lock());
}


void SpriteMaterial::setCameraMatrix(const glm::mat3 &cameraMatrix)
{
    m_cameraMatrix = cameraMatrix;
}


void SpriteMaterial::onBind() const
{
    Material::onBind();

    getShader().setUniform("uCameraProjectionMatrix", m_cameraMatrix);
}

}  // namespace game