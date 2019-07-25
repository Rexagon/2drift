// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "MainScene.hpp"

#include <iostream>

namespace game
{
game::MainScene::MainScene(core::Core &core)
    : Scene{core}
{
}


void MainScene::onUpdate(double dt)
{
    std::cout << dt << std::endl;
}

}  // namespace game
