set(2DRIFT_CORE_SRC
        Core/Core.cpp)

set(2DRIFT_MANAGERS_SRC
        Managers/Manager.cpp
        Managers/WindowManager.cpp
        Managers/InputManager.cpp
        Managers/ResourceManager.cpp)

set(2DRIFT_SRC
        ${2DRIFT_CORE_SRC}
        ${2DRIFT_MANAGERS_SRC}
        Application.cpp
        main.cpp)

add_executable(2drift ${2DRIFT_SRC})

target_include_directories(2drift
        PRIVATE ${CMAKE_SOURCE_DIR}/src)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2.5 CONFIG REQUIRED COMPONENTS
        system
        window
        network
        graphics
        audio)

target_link_libraries(2drift
        sfml-system
        sfml-window
        sfml-network
        sfml-graphics
        sfml-audio)
