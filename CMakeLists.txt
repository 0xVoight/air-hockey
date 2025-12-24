cmake_minimum_required(VERSION 3.16)
project(air-hockey LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# glfw
if(NOT EMSCRIPTEN)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

    add_subdirectory(external/glfw)
endif()

# glm
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE external)

# glad
if(EMSCRIPTEN)
    add_library(glad_web STATIC external/glad-web/src/glad.c)
    target_include_directories(glad_web PUBLIC external/glad-web/include)
else()
    add_library(glad STATIC external/glad/src/glad.c)
    target_include_directories(glad PUBLIC external/glad/include)
endif()

# src
set(SRC
    src/main.cpp
    src/app/Application.cpp
    src/core/Game.cpp
    src/core/Time.cpp
    src/physics/PhysicsWorld.cpp
    src/render/OpenGLRenderer.cpp
    src/render/WebGLRenderer.cpp
    src/platform/GlfwWindow.cpp
    src/platform/EmsWindow.cpp
)

add_executable(air-hockey ${SRC})

target_include_directories(air-hockey PRIVATE src)

target_link_libraries(air-hockey PRIVATE glm)

if(EMSCRIPTEN)
    target_link_libraries(air-hockey PRIVATE glad_web)
    target_link_options(air-hockey PRIVATE "-sUSE_WEBGL2=1")
else()
    target_link_libraries(air-hockey PRIVATE glad glfw)

    if (WIN32)
        target_link_libraries(air-hockey PRIVATE opengl32)
    else()
        find_package(OpenGL REQUIRED)
        target_link_libraries(air-hockey PRIVATE OpenGL::GL)
    endif()
endif()

include(GNUInstallDirs)
install(TARGETS air-hockey
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
