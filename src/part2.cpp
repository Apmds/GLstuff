/*
This part includes the subsections from "Textures" to "somewhere I'll decide when this gets too full" in the "Getting Started" section from learnopengl.com
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

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL - Part 2", NULL, NULL);
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

    // Shader
    uint shader;
    bool success = makeShaderProgram(&shader, "shaders/texture.vert", "shaders/texture.frag");
    if (!success) {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // Buffers and stuff
    uint VBO;
    glGenBuffers(1, &VBO); 
    
    uint EBO;
    glGenBuffers(1, &EBO); 

    uint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0); // vertPos
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*) (3*sizeof(float))); // vertColor
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*) (6*sizeof(float))); // texCoords
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char *data = stbi_load("textures/container.png", &width, &height, &nrChannels, 0);
    if (data == NULL) {
        fprintf(stderr, "Failed to load \"%s\"\n", "textures/container.png");
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // Generate texture and bind it
    uint tex_container;
    glGenTextures(1, &tex_container);
    glBindTexture(GL_TEXTURE_2D, tex_container);

    // Set filters and wrapping parameters (this can be done before loading the image data) (there exist default values already, but we need to set some when using mipmaps)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // Filter when zooming out
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // Filter when zooming in
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // X axis wrap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Y axis wrap

    // Put data in texture and generate mipmaps
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data); // Texture is loaded so no need for this anymore
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind because I can

    data = stbi_load("textures/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data == NULL) {
        fprintf(stderr, "Failed to load \"%s\"\n", "textures/awesomeface.png");
        glfwTerminate();
        return EXIT_FAILURE;
    }

    uint tex_face;
    glGenTextures(1, &tex_face);
    glBindTexture(GL_TEXTURE_2D, tex_face);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Por as localizações dos samplers das texturas no shader
    glUseProgram(shader);
    glUniform1i(glGetUniformLocation(shader, "texture1"), 0);
    glUniform1i(glGetUniformLocation(shader, "texture2"), 1);

    // Render loop
    float mix = 0.2;
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.39, 0.58, 0.93, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glBindVertexArray(VAO);

        // Definir as texturas baseado nas localizações dos uniformes
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex_container);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tex_face);

        double time = glfwGetTime();

        // Translation
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.4, -0.7, 0.0));
        trans = glm::rotate(trans, (float) time, glm::vec3(0.0f, 0.0f, 1.0f)); // glm overloads don't like if the second argument is a double
        
        //trans = glm::scale(trans, glm::vec3(abs(sin(time))));

        uint trans_loc = glGetUniformLocation(shader, "transform");
        glUniformMatrix4fv(trans_loc, 1, GL_FALSE, glm::value_ptr(trans));

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            mix += 0.01;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            mix -= 0.01;
        }
        if (mix > 1) mix = 1;
        if (mix < 0) mix = 0;

        
        glUniform1f(glGetUniformLocation(shader, "mixValue"), mix);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);


        trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(-1.0, 1.0, 0.0));
        trans = glm::scale(trans, glm::vec3(sin(time + 2)));
        glUniformMatrix4fv(trans_loc, 1, GL_FALSE, glm::value_ptr(trans));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}
