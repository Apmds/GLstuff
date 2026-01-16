#ifndef UTILS_H
#define UTILS_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>

// Helpers para carregar e compilar um shader
unsigned int loadShader(GLenum shader_type, const char* file_name);
bool compileShader(unsigned int shader);

#endif