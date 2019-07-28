#pragma once

#include <string>
#include <vector>

#include "Manager.hpp"

namespace core
{
/**
 * @brief   File manager
 *
 * Abstraction for all operations with files
 */
class FileManager final : public Manager
{
public:
    /**
     * @brief               Create file manager with specified root folder
     * @param core          Game core object
     * @param dataFolder    Root folder path. Last symbol must be '/'
     */
    explicit FileManager(Core &core, const std::string &dataFolder = "data/");

    /**
     * @brief               Load file
     * @param filename      File path relative to root folder
     * @return              File data as bytes array
     *
     * @throws              std::runtime_error if file was not found
     */
    std::vector<char> load(const std::string &filename);

private:
    std::string m_dataFolder;
};

}  // namespace core
