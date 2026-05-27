cmake_minimum_required(VERSION 3.15)
project(OpenGLDemo)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_C_COMPILER "gcc")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra)

find_package(OpenGL REQUIRED)

add_library(engine_deps STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/external/src/glad.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/src/stb_image.cpp
)
target_include_directories(engine_deps SYSTEM PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/external/include
)
target_link_libraries(engine_deps PUBLIC
    OpenGL::GL
    ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libglfw3.a
)

add_library(engine_core STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/system/WindowManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/render/Model.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/render/ModelManager.cpp
)
target_include_directories(engine_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(engine_core PUBLIC
    engine_deps
)

add_executable(demo
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)
target_link_libraries(demo PRIVATE
    engine_core
)