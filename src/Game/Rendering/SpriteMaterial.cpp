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

    false /* is face culling enabled */,
    GL_BACK /* face culling side */,

    GL_FILL /* polygon mode */,
};

}  // namespace

namespace game
{
SpriteMaterial::SpriteMaterial(Core &core, core::ResourcesScope &resourcesScope)
    : Material{core, RENDERING_PARAMETERS,
               resourcesScope
                   .get<Shader>(SPRITE_SHADER_NAME, ShaderLoader{core, SPRITE_VERTEX_SHADER, SPRITE_FRAGMENT_SHADER})
                   .lock()}
{
    getShader().bind();
    getShader().setUniform("uTexture", 0);
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

// SpriteMaterial::Parameters
//

void SpriteMaterial::Parameters::apply(core::Shader &shader) const
{
    shader.bind();
    shader.setUniform("uSize", m_size);
    shader.setUniform("uColor", m_color);
    shader.setUniform("uTransformationMatrix", m_transformation);

    shader.setUniform("uHasTexture", m_texture != nullptr);
    if (m_texture != nullptr)
    {
        m_texture->bind(SPRITE_TEXTURE_SLOT);
    }
}


void SpriteMaterial::Parameters::setSize(const glm::vec2 &size)
{
    m_size = size;
}


void SpriteMaterial::Parameters::setColor(const glm::vec4 &color)
{
    m_color = color;
}


void SpriteMaterial::Parameters::setTexture(const core::Texture *texture)
{
    m_texture = texture;
}


void SpriteMaterial::Parameters::setTransformation(const glm::mat3 &transformation)
{
    m_transformation = transformation;
}

}  // namespace game
