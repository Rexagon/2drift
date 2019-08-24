#pragma once

#include "Shader.hpp"
#include "Stuff/MaterialParameters.hpp"
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
    void bind(const MaterialParametersBase &materialParameters) const;

    Shader &getShader() const;

protected:
    void setShader(const std::shared_ptr<Shader> &shader);

    virtual void onBind() const;

    RenderingManager &getRenderingManager() const;

private:
    std::shared_ptr<RenderingManager> m_renderingManager;
    RenderingParameters m_renderingParameters;
    std::shared_ptr<Shader> m_shader;
};

}  // namespace core
