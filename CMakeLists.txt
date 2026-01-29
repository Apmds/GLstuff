cmake_minimum_required(VERSION 3.11...3.28 FATAL_ERROR) # Para ser igual ao do GLFW

project(LearnOpenGL)

# GLM
include(FetchContent)
FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	0af55ccecd98d4e5a8d1fad7de25ba429d60e863 #refs/tags/1.0.1
)
FetchContent_MakeAvailable(glm)


# Fetch stb_image.h
include(FetchContent)
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(stb)

# Biblioteca do glfw
add_library(glfw STATIC IMPORTED)
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/external/glfw")

add_library(glad)
set(GLAD_DIR "${CMAKE_SOURCE_DIR}/external/glad")

target_sources(glad
    PRIVATE
        ${GLAD_DIR}/src/glad.c
)
target_include_directories(glad
    PUBLIC
        ${GLAD_DIR}/include
)

set_target_properties(glfw PROPERTIES
    IMPORTED_LOCATION
        ${GLFW_DIR}/lib/libglfw3.a
    INTERFACE_INCLUDE_DIRECTORIES
        ${GLFW_DIR}/include
)

# Executáveis
add_executable(part1)
add_executable(part2)
add_executable(part3)

target_include_directories(part1
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include/
)
target_include_directories(part2
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include/
        ${stb_SOURCE_DIR}
        ${glm_SOURCE_DIR}
)
target_include_directories(part3
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include/
        ${stb_SOURCE_DIR}
        ${glm_SOURCE_DIR}
)

target_sources(part1
    PRIVATE
        src/part1.c
        src/utils.c
)
target_sources(part2
    PRIVATE
        src/part2.cpp
        src/utils.c
)
target_sources(part3
    PRIVATE
        src/part3.cpp
        src/camera.cpp
        src/utils.c
)

# Link the stuff within GLFW
target_link_libraries(glfw
    INTERFACE
        m
        GL
        X11
        pthread
        Xrandr
        Xi
        dl
)

# Link GLFW and GLAD
target_link_libraries(part1
    PRIVATE
        glfw
        glad
)
target_link_libraries(part2
    PRIVATE
        glfw
        glad
        glm::glm
)
target_link_libraries(part3
    PRIVATE
        glfw
        glad
        glm::glm
)
