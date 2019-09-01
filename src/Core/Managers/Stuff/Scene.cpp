// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Scene.hpp"

namespace core
{
Scene::Scene(Core &core)
    : m_core{core}
{
}


void Scene::init()
{
}

void Scene::close()
{
}


void Scene::handleEvent(const Event & /*e*/)
{
}


void Scene::update(float /*dt*/)
{
}

}  // namespace core
