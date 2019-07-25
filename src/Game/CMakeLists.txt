set(GAME_SRC
        main.cpp
        Game.cpp

        Scenes/MainScene.cpp)

add_executable(game ${GAME_SRC})

target_include_directories(game
        PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(game core)

set_target_properties(game PROPERTIES OUTPUT_NAME "2drift")
