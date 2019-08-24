// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Material.hpp"

#include "Core/Core.hpp"

namespace core
{
Material::Material(Core &core, const RenderingParameters &renderingParameters, const std::shared_ptr<Shader> &shader)
    : m_renderingManager{core.get<RenderingManager>().lock()}
    , m_renderingParameters{renderingParameters}
    , m_shader{shader}
{
}


void Material::bind() const
{
    assert(m_shader != nullptr);
    m_shader->bind();
    m_renderingManager->setRenderingParameters(m_renderingParameters);

    onBind();
}


void Material::bind(const ShaderParameters &shaderParameters) const
{
    assert(m_shader != nullptr);
    m_shader->bind();
    m_renderingManager->setRenderingParameters(m_renderingParameters);

    shaderParameters.apply(*m_shader);

    onBind();
}


void Material::onBind() const
{
}


RenderingManager &Material::getRenderingManager() const
{
    return *m_renderingManager;
}


void Material::setRenderingParameters(const core::RenderingParameters &renderingParameters)
{
    m_renderingParameters = renderingParameters;
}


const RenderingParameters &Material::getRenderingParameters() const
{
    return m_renderingParameters;
}


void Material::setShader(const std::shared_ptr<Shader> &shader)
{
    m_shader = shader;
}


Shader &Material::getShader() const
{
    return *m_shader;
}

}  // namespace core
