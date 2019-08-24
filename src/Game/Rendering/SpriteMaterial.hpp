#pragma once

#include <Core/Rendering/Material.hpp>
#include <Core/Rendering/Stuff/ShaderParameters.hpp>
#include <Core/Resources/Stuff/ResourcesScope.hpp>

namespace game
{
class SpriteMaterial final : public core::Material
{
public:
    class Parameters : public core::ShaderParameters
    {
    public:
        void apply(core::Shader &shader) const override;

        void setSize(const glm::vec2 &size);
        void setColor(const glm::vec4 &color);

        void setTransformation(const glm::mat3 &transformation);

    private:
        glm::vec2 m_size{1.0f, 1.0f};
        glm::vec4 m_color{0.0f, 0.0f, 0.0f, 1.0f};

        glm::mat3 m_transformation{1.0f};
    };

    explicit SpriteMaterial(core::Core &core);

    void setCameraMatrix(const glm::mat3 &cameraMatrix);

protected:
    void onBind() const override;

private:
    glm::mat3 m_cameraMatrix{1.0f};

    core::ResourcesScope m_resourcesScope;
};

}  // namespace game
