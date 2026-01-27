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
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // X, Y, Z, R, G, B, S, T
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
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

    // Vertex array
    uint vertex_array; glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

    // Buffer data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0); // vertPos
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float))); // vertColor
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float))); // texCoords
    glEnableVertexAttribArray(2);

    // Model matrix (local coords to world coords)
    glm::mat4 model = glm::mat4(1.0f);

    // View matrix (world coords to camera coords)
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    // Projection matrix (camera coords to normalized range (-1 to 1))
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, 100.0f);

    // Make opengl use the depth buffer for drawing
    glEnable(GL_DEPTH_TEST);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2, 0.3, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Also clear depth buffer

        glBindVertexArray(vertex_array);
        glUseProgram(shader);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, containerTex);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, faceTex);        

        // Send matrices to vertex shader
        glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shader, "proj"), 1, GL_FALSE, glm::value_ptr(proj));
        
        for (int i = 0; i < 10; i++) {
            model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
            model = glm::rotate(model, (float)i*20.0f, glm::vec3(0.0f, 1.0f, -0.5f));
            glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glUseProgram(0);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Unload (not strictly needed because memory is used throughout the whole program)
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteVertexArrays(1, &vertex_array);
    glDeleteProgram(shader);
    glDeleteTextures(1, &containerTex);
    glDeleteTextures(1, &faceTex);

    glfwTerminate();
    return EXIT_SUCCESS;
}
