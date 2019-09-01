#pragma once

#include <tuple>

#include "../Shader.hpp"

namespace core
{
class ShaderParameters
{
public:
    virtual ~ShaderParameters() = default;

    virtual void apply(Shader &shader) const = 0;
};

}  // namespace core
