set(CORE_SRC
        Core.cpp

        Managers/Manager.cpp
        Managers/WindowManager.cpp
        Managers/InputManager.cpp
        Managers/ResourceManager.cpp
        Managers/FileManager.cpp
        Managers/SceneManager.cpp

        Rendering/RenderingQueue.cpp

        Resources/ResourcesScope.cpp
        Resources/TextureLoader.cpp

        Stuff/Time.cpp)

add_library(core OBJECT ${CORE_SRC})

target_include_directories(core
        PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(core PUBLIC
        sfml-system
        sfml-window
        sfml-network
        sfml-graphics
        sfml-audio)

target_compile_features(core PUBLIC cxx_std_17)

target_compile_options(core PUBLIC
        -Werror
        -Wall
        -Wextra
        -Wpedantic
        -Wcast-align
        -Wcast-qual
        -Wconversion
        -Wctor-dtor-privacy
        -Wenum-compare
        -Wfloat-equal
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Woverloaded-virtual
        -Wredundant-decls
        -Wsign-conversion
        -Wsign-promo)
