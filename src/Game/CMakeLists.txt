set(GAME_SRC
        main.cpp

        Rendering/ScreenMaterial.cpp
        Rendering/SpriteMaterial.cpp

        Scenes/MainScene.cpp

        Stuff/SharedState.cpp

        Systems/CameraMovementSystem.cpp
        Systems/CameraResizingSystem.cpp
        Systems/CarMovementSystem.cpp
        Systems/InputSystem.cpp
        Systems/RenderingSystem.cpp
        Systems/SpriteRenderingSystem.cpp
        Systems/WheelsPositioningSystem.cpp)

add_executable(game ${GAME_SRC})

target_include_directories(game
        PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(game core EnTT)

set_target_properties(game PROPERTIES
        OUTPUT_NAME "2drift"
        RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR})

add_custom_command(TARGET game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res ${BUILD_OUTPUT_DIR}/data)
