#pragma once

#include <memory>

#include "Managers/FileManager.hpp"

namespace app
{
class TextureLoader
{
public:
    explicit TextureLoader(Core &core, const std::string &path);
    explicit TextureLoader(const std::shared_ptr<FileManager> &fileManager, const std::string &path);

    std::shared_ptr<void> operator()();

private:
    std::shared_ptr<FileManager> m_fileManager;

    std::string m_path;
};

}  // namespace app
