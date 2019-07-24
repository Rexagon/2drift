// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ResourcesScope.hpp"

namespace app
{
ResourcesScope::ResourcesScope(const std::shared_ptr<ResourceManager> &manager)
    : m_resourceManager(manager)
{
}


ResourcesScope::~ResourcesScope()
{
    for (const auto &key : m_resources)
    {
        m_resourceManager->unbind(key);
        m_resourceManager->clear(key);
    }
}


}  // namespace app
