// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Manager.hpp"

namespace core
{
Manager::Manager(Core &core)
    : m_core{core}
    , m_isInitialized{false}
{
}

void Manager::init()
{
    if (m_isInitialized)
    {
        return;
    }

    onInit();

    m_isInitialized = true;
}

void Manager::onInit()
{
}


Core &Manager::getCore()
{
    return m_core;
}

}  // namespace core
