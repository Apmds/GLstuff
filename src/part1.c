/*
This part includes the subsections from "OpenGL" to "Shaders" in the "Getting Started" section from learnopengl.com
*/

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "utils.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

float vertices[] = {
    -0.7f, -0.7f, 0.0f, 1.0f, 0.0f, 0.0f, // X, Y, Z, R, G, B
     0.3f,  0.3f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.7f,  0.3f, 0.0f, 0.0f, 0.0f, 1.0f,
     0.3f, -0.7f, 0.0f, 1.0f, 1.0f, 1.0f,
};

float vertices2[] = {
     -0.9f,  0.9f, 0.0f, 1.0f, 0.0f, 0.0f, // X, Y, Z, R, G, B
     -0.9f,  0.8f, 0.0f, 0.0f, 1.0f, 0.0f,
     -0.85f, 0.85f, 0.0f, 0.0f, 0.0f, 1.0f,
};

unsigned int indices[] = {
    0, 1, 2,
    0, 1, 3,
};

bool wireframe = false;

// Called when the window size changes (changes the openGL framebuffer to match the new framebuffer size)
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Processes the key input for the given window
void process_input_key(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        if (!wireframe) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        wireframe = !wireframe;
    }
}

int main() {
    glfwInit();
    
    // OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Isto é específicamente preciso para MacOS  -\_shi_/-
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // Create window and set context
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL - Part 1", NULL, NULL);
    if (window == NULL) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, process_input_key);

    // Pedir ao GLAD para carregar as funções do OpenGL (passamos a função do GLFW que faz isso baseado no sistema operativo)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD");
        return -1;
    }

    // Create the actual openGL viewport with the dimensions of the window
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Shader programs    
    unsigned int rainbow_shader;
    if (!makeShaderProgram(&rainbow_shader, "shaders/rainbow.vert", "shaders/rainbow.frag")) {
        return -1;
    }

    unsigned int yellow_shader;
    if (!makeShaderProgram(&yellow_shader, "shaders/yellow.vert", "shaders/yellow.frag")) {
        return -1;
    }

    // Criar vertex buffer na gpu e meter como array buffer
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Criar vertex array para guardar o vertex buffer e as configurações de atributos
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    // Enviar os vertices do triangulo para a gpu como memória estática (write once, read many)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Colocar atributos de vertice no buffer object
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0); // 3 floats

    // Dá para fazer também desta forma quando sabemos o shader que vamos usar com estes vértices
    unsigned int element_attr = glGetAttribLocation(rainbow_shader, "color");
    glEnableVertexAttribArray(element_attr);
    glVertexAttribPointer(element_attr, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float))); // 3 floats

    // Criar um EBO para guardar os indices dos vértices a desenhar
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // Unbind da VAO (não seria preciso aqui especificamente porque não damos setup a mais nenhum vertex array)
    glBindVertexArray(0);
    
    // Dei unbind do vertex e element buffers também só para mostrar que VBO e EBO estão associados a VAO agora
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    unsigned int yellow_VBO;
    glGenBuffers(1, &yellow_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, yellow_VBO);
    
    unsigned int yellow_VAO;
    glGenVertexArrays(1, &yellow_VAO);
    glBindVertexArray(yellow_VAO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);

    element_attr = glGetAttribLocation(yellow_shader, "color");
    glEnableVertexAttribArray(element_attr);
    glVertexAttribPointer(element_attr, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Definir blend mode para transparência
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Desenhar o quadrado guardado na VAO
        glUseProgram(rainbow_shader);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Triangulo pequeno
        glUseProgram(yellow_shader);
        
        // Atualizar uniform (o valor fica guardado por default no programa então poderíamos não atualizar todos os frames)
        float time = glfwGetTime();
        float transparency = (sin(time) / 2) + 0.5;
        
        shaderSet(yellow_shader, "transparency", transparency);
        shaderSet(yellow_shader, "horizontalShift", time*0.1f);
        
        glBindVertexArray(yellow_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
