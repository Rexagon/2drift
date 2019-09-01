#pragma once

#include "Core/Rendering/Stuff/ShaderParameters.hpp"
#include "Stuff/RenderingParameters.hpp"

namespace core
{
class Material
{
public:
    explicit Material(Core &core,
                      const RenderingParameters &renderingParameters,
                      const std::shared_ptr<Shader> &shader);

    virtual ~Material() = default;

    void bind() const;
    void bind(const ShaderParameters &shaderParameters) const;

protected:
    virtual void onBind() const;

    RenderingManager &getRenderingManager() const;

    void setRenderingParameters(const RenderingParameters &renderingParameters);
    const RenderingParameters &getRenderingParameters() const;

    void setShader(const std::shared_ptr<Shader> &shader);
    Shader &getShader() const;

private:
    std::shared_ptr<RenderingManager> m_renderingManager;

    RenderingParameters m_renderingParameters;
    std::shared_ptr<Shader> m_shader;
};

}  // namespace core
