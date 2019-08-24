#pragma once

#include <glad/glad.h>

namespace core
{
struct RenderingParameters final
{
    bool isDepthTestEnabled{false};
    bool isDepthWriteEnabled{false};
    GLenum depthTestFunction{GL_LEQUAL};

    bool isBlendingEnabled{true};
    GLenum blendingFunctionSrc{GL_SRC_ALPHA};
    GLenum blendingFunctionDst{GL_ONE_MINUS_SRC_ALPHA};

    bool isFaceCullingEnabled{true};
    GLenum faceCullingSide{GL_BACK};

    GLenum polygonMode{GL_FILL};
};

}  // namespace core
