cmake_minimum_required(VERSION 3.15)

project(OpenGLDemo)

# cpp/c configure
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_C_COMPILER "gcc")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# OpenGL
find_package(OpenGL REQUIRED)

set(EXTERNAL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/include)
set(GLFW_LIBRARY         ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libglfw3.a)
set(EXTERNAL_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/external/src/glad.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/src/stb_image.cpp
)

set(INCLUDE_DIR include)

set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/system/WindowManager.cpp
)

add_executable(demo
    ${EXTERNAL_SRC}
    ${SRC}
)

target_include_directories(demo 
    PRIVATE
    ${EXTERNAL_INCLUDE_DIR}
    ${INCLUDE_DIR}
)

target_link_libraries(demo PRIVATE
    OpenGL::GL
    ${GLFW_LIBRARY}
)