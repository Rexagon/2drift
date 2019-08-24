// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ShaderLoader.hpp"

#include "Core/Core.hpp"
#include "Core/Rendering/Shader.hpp"

namespace core
{
ShaderLoader::ShaderLoader(Core &core, const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
    : m_core{core}
    , m_fileManager{core.get<FileManager>().lock()}
    , m_vertexShaderPath{vertexShaderPath}
    , m_fragmentShaderPath{fragmentShaderPath}
{
}


std::shared_ptr<void> ShaderLoader::operator()()
{
    auto shader = std::make_shared<Shader>(m_core);

    std::string error;

    // Load vertex shader part
    {
        const auto data = m_fileManager->load(m_vertexShaderPath);
        if (!shader->attachPart(data, GL_VERTEX_SHADER, error))
        {
            throw std::runtime_error{"Unable to load vertex shader: " + m_vertexShaderPath + ". \n" + error};
        }
    }

    // Load fragment shader part
    {
        const auto data = m_fileManager->load(m_fragmentShaderPath);
        if (!shader->attachPart(data, GL_FRAGMENT_SHADER, error))
        {
            throw std::runtime_error{"Unable to load fragment shader: " + m_fragmentShaderPath + ".\n" + error};
        }
    }

    if (!shader->link(error))
    {
        throw std::runtime_error{"Unable to link shader programs: " + m_vertexShaderPath + ", " + m_fragmentShaderPath +
                                 ".\n" + error};
    }

    return shader;
}


}  // namespace core
