#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Called when the window size changes (changes the openGL framebuffer to match the new framebuffer size)
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Processes the key input for the given window
void process_input(GLFWwindow* window);

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.0f, 0.0f,
};

// Helpers para carregar e compilar um shader
unsigned int loadShader(GLenum shader_type, const char* shader_code);
bool compileShader(unsigned int shader);

const char* vertex_shader_code = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n"
;

const char* fragment_shader_code = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n"
;

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
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Pedir ao GLAD para carregar as funções do OpenGL (passamos a função do GLFW que faz isso baseado no sistema operativo)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD");
        return -1;
    }

    // Create the actual openGL viewport with the dimensions of the window
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);


    // Criar buffer na gpu e meter como array buffer
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Enviar os vertices do triangulo para a gpu como memória estática (write once, read many)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Shaders básicos
    unsigned int vertex_shader = loadShader(GL_VERTEX_SHADER, vertex_shader_code);
    if (!compileShader(vertex_shader)) {
        return -1;
    }

    unsigned int fragment_shader = loadShader(GL_VERTEX_SHADER, fragment_shader_code);
    if (!compileShader(fragment_shader)) {
        return -1;
    }

    // Linkar shaders num program
    unsigned int shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    int success;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if(!success) {
        char infoLog[512];
        glGetProgramInfoLog(shader_program, sizeof(infoLog), NULL, infoLog);
        printf("%s\n", infoLog);
        return -1;
    }

    // Pode-se apagar os shaders depois de linkar
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

unsigned int loadShader(GLenum shader_type, const char* shader_code) {
    unsigned int shader = glCreateShader(shader_type);

    glShaderSource(shader, 1, &shader_code, NULL);
    
    return shader;
}

bool compileShader(unsigned int shader) {
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
        printf("%s\n", infoLog);
        return false;
    }

    return true;
}