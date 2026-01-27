/*
This part includes the subsections from "Coordinate Systems" to "Review" in the "Getting Started" section from learnopengl.com
*/

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "utils.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef unsigned int uint;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

float vertices[] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // X, Y, Z, R, G, B, S, T
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
};

uint indices[] = {
    0, 1, 2,
    0, 2, 3,
};

// Called when the window size changes (changes the openGL framebuffer to match the new framebuffer size)
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Processes the key input for the given window
void process_input_key(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    // Boring setup
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL - Part 3", NULL, NULL);
    if (window == NULL) {
        const char* errorMsg;
        glfwGetError(&errorMsg);
        fprintf(stderr, "Window could not be created: %s\n", errorMsg);
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        fprintf(stderr, "GLAD did NOT load OpenGL functions\n");
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, process_input_key);

    // Load textures
    uint containerTex;
    if (!createTexture(&containerTex, "textures/container.png", true, false)) {
        fprintf(stderr, "Couldn't load image :(\n");
        glfwTerminate();
        return EXIT_FAILURE;
    }
    textureSetFilter(containerTex, GL_LINEAR_MIPMAP_LINEAR, GL_NEAREST);

    uint faceTex;
    if (!createTexture(&faceTex, "textures/awesomeface.png", true, true)) {
        fprintf(stderr, "Couldn't load image :(\n");
        glfwTerminate();
        return EXIT_FAILURE;
    }
    textureSetFilter(faceTex, GL_LINEAR_MIPMAP_LINEAR, GL_NEAREST);

    // Shader
    uint shader;
    if (!makeShaderProgram(&shader, "shaders/part3.vert", "shaders/part3.frag")) {
        fprintf(stderr, "Couldn't compile shader :(\n");
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glUseProgram(shader);
    glUniform1i(glGetUniformLocation(shader, "bgTex"), 0); // Texture locations
    glUniform1i(glGetUniformLocation(shader, "fgTex"), 1);

    // Buffers
    uint vertex_buffer; glGenBuffers(1, &vertex_buffer);
    uint element_buffer; glGenBuffers(1, &element_buffer);

    // Vertex array
    uint vertex_array; glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);

    // Buffer data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0); // vertPos
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float))); // vertColor
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float))); // texCoords
    glEnableVertexAttribArray(2);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2, 0.3, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vertex_array);
        glUseProgram(shader);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, containerTex);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, faceTex);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

        glUseProgram(0);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Unload (not strictly needed because memory is used throughout the whole program)
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteBuffers(1, &element_buffer);
    glDeleteVertexArrays(1, &vertex_array);
    glDeleteProgram(shader);
    glDeleteTextures(1, &containerTex);
    glDeleteTextures(1, &faceTex);

    glfwTerminate();
    return EXIT_SUCCESS;
}
