#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

// Helpers para carregar e compilar um shader
unsigned int loadShader(GLenum shader_type, const char* file_name) {
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        fprintf(stderr, "File \"%s\" not found!\n", file_name);
    }
    
    // Go to end of file and get the size
    fseek(file, 0, SEEK_END);
    int filelength = ftell(file) + 1;

    fclose(file);

    char* shader_code = malloc(filelength);
    shader_code[filelength-1] = '\0';
    file = fopen(file_name, "r");
    if (file == NULL) {
        fprintf(stderr, "File \"%s\" not found!\n", file_name);
    }

    fread(shader_code, filelength, sizeof(char), file);
    fclose(file);


    unsigned int shader = glCreateShader(shader_type);

    const char* const_shader_code = shader_code;
    glShaderSource(shader, 1, &const_shader_code, NULL);

    free(shader_code);
    
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

