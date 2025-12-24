cmake_minimum_required(VERSION 3.16)

project(air-hockey LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/glfw)

add_executable(air-hockey
    src/main.cpp
    src/app/Application.cpp
    src/core/Game.cpp
    src/core/Time.cpp
    src/math/Math.cpp
    src/physics/PhysicsWorld.cpp
    src/render/OpenGLRenderer.cpp
    src/platform/GlfwWindow.cpp
)

target_include_directories(air-hockey PRIVATE src)

target_link_libraries(air-hockey PRIVATE glfw)

if (WIN32)
    target_link_libraries(air-hockey PRIVATE opengl32)
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(air-hockey PRIVATE OpenGL::GL)
endif()

include(GNUInstallDirs)
install(TARGETS air-hockey
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
