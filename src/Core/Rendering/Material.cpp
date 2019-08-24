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

    m_renderingManager->setRenderingParameters(m_renderingParameters);
    m_shader->bind();

    onBind();
}


void Material::bind(const MaterialParametersBase &materialParameters) const
{
    assert(m_shader != nullptr);

    m_renderingManager->setRenderingParameters(m_renderingParameters);
    m_shader->bind();

    materialParameters.apply(*m_shader);

    onBind();
}


Shader &Material::getShader() const
{
    assert(m_shader != nullptr);

    return *m_shader;
}


void Material::setShader(const std::shared_ptr<Shader> &shader)
{
    m_shader = shader;
}


void Material::onBind() const
{
}


RenderingManager &Material::getRenderingManager() const
{
    return *m_renderingManager;
}

}  // namespace core
