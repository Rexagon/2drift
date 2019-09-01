#include <iostream>

#include <Core/Managers/FileManager.hpp>
#include <Core/Managers/InputManager.hpp>
#include <Core/Managers/RenderingManager.hpp>
#include <Core/Managers/ResourceManager.hpp>
#include <Core/Managers/SceneManager.hpp>
#include <Core/Managers/WindowManager.hpp>

#include <Core/Stuff/Time.hpp>

#include "Scenes/MainScene.hpp"

using namespace core;
using namespace game;

namespace
{
constexpr auto WINDOW_TITLE = "2drift";
}


void init(Core &core)
{
    core.bind<FileManager>();
    core.bind<WindowManager>(glm::uvec2{1024, 768}, WINDOW_TITLE);
    core.bind<InputManager>();
    core.bind<RenderingManager>();
    core.bind<ResourceManager>();

    core.bind<SceneManager>();

    core.init();

    core.get<WindowManager>().lock()->setVsyncEnabled(true);

    core.get<SceneManager>().lock()->openScene(createMainScene(core));
}


void run(Core &core)
{
    // Cache managers
    auto inputManager = core.get<InputManager>().lock();
    auto sceneManager = core.get<SceneManager>().lock();
    auto windowManager = core.get<WindowManager>().lock();

    // Main game loop
    auto timeBefore = core::time::now();

    while (!core.isPendingStop())
    {
        // Calculate delta time
        const auto timeAfter = core::time::now();
        const float dt = core::time::DurationSeconds{timeAfter - timeBefore}.count();
        timeBefore = timeAfter;

        // Prepare managers for frame
        inputManager->reset();

        // Handle events
        Event e{};
        while (windowManager->pollEvent(e))
        {
            // Internal handle
            switch (e.type)
            {
                case Event::Type::Closed:
                    // Close application after this frame
                    core.requestExit();
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
        windowManager->display();
    }
}


int main()
{
    Core core;

    try
    {
        init(core);
        run(core);
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "CRITICAL ERROR: " << e.what() << std::endl;
        return 1;
    }
}
