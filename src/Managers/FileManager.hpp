#pragma once

#include <string>
#include <vector>

#include "Manager.hpp"

namespace app
{
class FileManager : public Manager
{
public:
    explicit FileManager(Core &core, const std::string &dataFolder = "data/");

    std::vector<char> load(const std::string &filename);

private:
    std::string m_dataFolder;
};
}  // namespace app
