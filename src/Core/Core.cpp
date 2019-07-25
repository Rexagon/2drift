// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Core.hpp"

namespace core
{
void Core::init()
{
    for (auto &[key, value] : m_managers)
    {
        value->init();
    }
}


void Core::requestExit()
{
    m_isPendingStop = true;
}


bool Core::isPendingStop() const
{
    return m_isPendingStop;
}

}  // namespace core
