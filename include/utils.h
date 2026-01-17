#ifndef UTILS_H
#define UTILS_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>

// Helpers para carregar e compilar um shader
unsigned int loadShader(GLenum shader_type, const char* file_name);
bool compileShader(unsigned int shader);

// Criar program e linkar shaders nele
bool makeShaderProgram(unsigned int* progp, unsigned int vertex_shader, unsigned int fragment_shader);

#endif