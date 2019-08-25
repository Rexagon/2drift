#pragma once

#include <memory>

#include "Core/Managers/FileManager.hpp"

namespace core
{
/**
 * @brief   Simple texture loader
 */
class TextureLoader
{
public:
    explicit TextureLoader(Core &core, const std::string &path);

    std::shared_ptr<void> operator()();

private:
    Core &m_core;
    std::shared_ptr<FileManager> m_fileManager;

    std::string m_path;
};

}  // namespace core
