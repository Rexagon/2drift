// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Game.hpp"

#include <Core/Managers/FileManager.hpp>
#include <Core/Managers/InputManager.hpp>
#include <Core/Managers/ResourceManager.hpp>
#include <Core/Managers/SceneManager.hpp>
#include <Core/Managers/WindowManager.hpp>

#include "Stuff/Scene.hpp"

#include "Systems/CameraResizingSystem.hpp"
#include "Systems/RenderingSystem.hpp"
#include "Systems/SpriteRenderingSystem.hpp"

using namespace core;

namespace
{
constexpr auto WINDOW_TITLE = "2drift";
}


namespace game
{
Game::Game()
{
    m_core.bind<FileManager>();
    m_core.bind<InputManager>();
    m_core.bind<ResourceManager>();
    m_core.bind<WindowManager>(sf::Vector2u(1024, 768), WINDOW_TITLE);

    m_core.bind<SceneManager>();

    m_core.init();

    createScene();
}


void Game::run()
{
    // Cache managers
    auto inputManager = m_core.get<InputManager>().lock();
    auto sceneManager = m_core.get<SceneManager>().lock();
    auto windowManager = m_core.get<WindowManager>().lock();

    // Main game loop
    auto &window = windowManager->getWindow();

    sf::Clock time;

    while (!m_core.isPendingStop())
    {
        // Calculate delta time
        const double dt = static_cast<double>(time.restart().asSeconds());

        // Prepare managers for frame
        inputManager->reset();

        // Handle events
        sf::Event e{};
        while (window.pollEvent(e))
        {
            // Internal handle
            switch (e.type)
            {
                case sf::Event::Closed:
                    // Close application after this frame
                    m_core.requestExit();
                    break;

                default:
                    break;
            }

            // Managers handle
            inputManager->handleEvent(e);
            sceneManager->handleEvent(e);
        }

        // Update scene
        sceneManager->update(dt);

        // Display image
        window.display();
    }
}


void Game::createScene()
{
    using SceneSystems = Systems<CameraResizingSystem, SpriteRenderingSystem, RenderingSystem>;

    auto scene = std::make_unique<Scene<SharedState, SceneSystems>>(m_core);

    auto &state = scene->getState();

    state.getRegistry().create<MainCamera, TransformComponent, CameraComponent, WindowResizeableComponent>();

    auto spriteEntity = state.getRegistry().create();
    state.getRegistry().assign<SpriteComponent>(
        spriteEntity, SpriteComponent{RenderingLayer::GROUND, 0, sf::RectangleShape{sf::Vector2f{100.0f, 100.0f}}});


    // Push created scene
    auto sceneManager = m_core.get<SceneManager>().lock();
    sceneManager->openScene(std::move(scene));
}

}  // namespace game
