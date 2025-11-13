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

# glfw
set(GLFW_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/include/")
set(GLFW_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/lib/libglfw3.a")

# glad
set(GLAD_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include")
set(GLAD_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/src/glad.c")

# glm
set(GLM_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/glm/")

# stb_image
set(STB_IMAGE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/stb_image/include")
set(STB_IMAGE_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/external/stb_image/src/stb_image.cpp")

# assimp
set(ASSIMP_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/assimp/include")
set(ASSIMP_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/external/assimp/lib/libassimp.dll.a")

# src
aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/src" SRC_DIR)

#build
add_executable(demo ${GLAD_SOURCE} ${STB_IMAGE_SOURCE} ${SRC_DIR})

target_include_directories(demo 
    PRIVATE
    ${GLFW_INCLUDE_DIR}
    ${GLAD_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
    ${STB_IMAGE_INCLUDE_DIR}
    ${ASSIMP_INCLUDE_DIR}
)

target_link_libraries(demo
    PRIVATE
    OpenGL::GL
    ${GLFW_LIBRARY}
    ${ASSIMP_LIBRARY}
)