// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "FileManager.hpp"

#include <fstream>

namespace core
{
FileManager::FileManager(Core &core, const std::string &dataFolder)
    : Manager{core}
    , m_dataFolder{dataFolder}
{
}


std::vector<char> FileManager::load(const std::string &filename)
{
    std::ifstream file{m_dataFolder + filename, std::ios_base::binary};

    if (!file.is_open())
    {
        throw std::runtime_error{"Unable to open file: " + m_dataFolder + filename};
    }

    std::vector<char> result;

    file.seekg(0, std::ios::end);
    result.resize(file.tellg());

    file.seekg(0, std::ios::beg);
    file.read(&result[0], result.size());

    file.close();

    return result;
}

}  // namespace core
