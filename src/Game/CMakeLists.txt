set(GAME_SRC
        main.cpp
        Game.cpp

        Stuff/System.cpp
        Systems/RenderingSystem.cpp
        Systems/SpriteRenderingSystem.cpp Stuff/SharedState.cpp)

add_executable(game ${GAME_SRC})

target_include_directories(game
        PRIVATE ${CMAKE_SOURCE_DIR}/src)

find_package(EnTT REQUIRED)

target_link_libraries(game core EnTT)

set_target_properties(game PROPERTIES OUTPUT_NAME "2drift")
