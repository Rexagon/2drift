#pragma once

#include <glad/glad.h>
#include <glm/vec3.hpp>

#include "Texture.hpp"

namespace core
{
class FrameBuffer final
{
public:
    explicit FrameBuffer(Core &core, const glm::uvec2 &size);
    ~FrameBuffer();

    void bind() const;

    void resize(const glm::uvec2 &size);

    Texture &getColorTexture();

    GLuint getHandle();

private:
    std::shared_ptr<RenderingManager> m_renderingManager;

    GLuint m_id{0};

    Texture m_colorTexture;
};

}  // namespace core
