cmake_minimum_required(VERSION 3.4...3.28 FATAL_ERROR) # Para ser igual ao do GLFW

project(LearnOpenGL C)

# Biblioteca do glfw
add_library(glfw STATIC IMPORTED)
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/external/glfw")


set_target_properties(glfw PROPERTIES
    IMPORTED_LOCATION
        ${GLFW_DIR}/lib/libglfw3.a
    INTERFACE_INCLUDE_DIRECTORIES
        ${GLFW_DIR}/include
)

# Executável
add_executable(opengl)

target_include_directories(opengl
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include/
)

target_sources(opengl
    PRIVATE
        src/main.c
        src/glad.c
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

# Link GLFW
target_link_libraries(opengl
    PRIVATE
        glfw
)
