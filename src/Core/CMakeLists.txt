set(CORE_SRC
        Core.cpp

        Managers/Stuff/Scene.cpp
        Managers/Manager.cpp
        Managers/WindowManager.cpp
        Managers/InputManager.cpp
        Managers/ResourceManager.cpp
        Managers/RenderingManager.cpp
        Managers/FileManager.cpp
        Managers/SceneManager.cpp

        Rendering/FrameBuffer.cpp
        Rendering/Mesh.cpp
        Rendering/Material.cpp
        Rendering/Stuff/MeshGeometry.cpp
        Rendering/Stuff/RenderingQueue.cpp
        Rendering/Texture.cpp
        Rendering/Shader.cpp

        Resources/Stuff/ResourcesScope.cpp
        Resources/ShaderLoader.cpp
        Resources/TextureLoader.cpp

        Stuff/Keyboard.cpp
        Stuff/Time.cpp)

add_library(core OBJECT ${CORE_SRC})

target_include_directories(core
        PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(core PUBLIC glfw glad stb glm opengl32 gdi32)

target_compile_definitions(core PUBLIC GLFW_INCLUDE_NONE)

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
