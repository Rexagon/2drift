set(GAME_SRC
        main.cpp

        Scenes/MainScene.cpp

        Stuff/SharedState.cpp

        Systems/CameraResizingSystem.cpp
        Systems/CarMovementSystem.cpp
        Systems/InputSystem.cpp
        Systems/RenderingSystem.cpp
        Systems/SpriteRenderingSystem.cpp)

add_executable(game ${GAME_SRC})

target_include_directories(game
        PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(game core EnTT)

set_target_properties(game PROPERTIES
        OUTPUT_NAME "2drift"
        RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR})

add_custom_command(TARGET game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory $ENV{SFML_DIR}/../../../bin ${BUILD_OUTPUT_DIR}/)
