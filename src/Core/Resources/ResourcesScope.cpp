// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ResourcesScope.hpp"

#include "Core/Core.hpp"

namespace core
{
ResourcesScope::ResourcesScope(Core &core)
    : m_resourceManager(core.get<ResourceManager>().lock())
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


}  // namespace core
