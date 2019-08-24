#pragma once

#include <memory>

#include "Core/Managers/FileManager.hpp"

namespace core
{
class ShaderLoader final
{
public:
    explicit ShaderLoader(Core &core, const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

    std::shared_ptr<void> operator()();

private:
    Core &m_core;
    std::shared_ptr<FileManager> m_fileManager;

    std::string m_vertexShaderPath;
    std::string m_fragmentShaderPath;
};

}  // namespace core
