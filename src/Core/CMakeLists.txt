set(CORE_SRC
        Core.cpp

        Managers/Manager.cpp
        Managers/WindowManager.cpp
        Managers/InputManager.cpp
        Managers/ResourceManager.cpp
        Managers/FileManager.cpp
        Managers/SceneManager.cpp

        Resources/ResourcesScope.cpp
        Resources/TextureLoader.cpp

        Stuff/Time.cpp)

add_library(core OBJECT ${CORE_SRC})

target_include_directories(core
        PRIVATE ${CMAKE_SOURCE_DIR}/src)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2.5 CONFIG REQUIRED COMPONENTS
        system
        window
        network
        graphics
        audio)

target_link_libraries(core PUBLIC
        sfml-system
        sfml-window
        sfml-network
        sfml-graphics
        sfml-audio)
