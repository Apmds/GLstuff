#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "stb_image.h"

// Helpers para carregar e compilar um shader
static unsigned int loadShader(GLenum shader_type, const char* file_name) {
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

static bool compileShader(unsigned int shader) {
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        int shaderType;
        glGetShaderiv(shader, GL_SHADER_TYPE, &shaderType);

        char infoLog[512];
        glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
        printf("Error compiling %s shader: %s\n", shaderType == GL_FRAGMENT_SHADER ? "fragment" : "vertex", infoLog);
        return false;
    }

    return true;
}

// Criar program e linkar shaders nele
bool makeShaderProgram(unsigned int* progp, const char* vertex_code, const char* fragment_code) {
    unsigned int vertex_shader = loadShader(GL_VERTEX_SHADER, vertex_code);
    if (!compileShader(vertex_shader)) {
        return false;
    }

    unsigned int fragment_shader = loadShader(GL_FRAGMENT_SHADER, fragment_code);
    if (!compileShader(fragment_shader)) {
        return false;
    }

    *progp = glCreateProgram();
    unsigned int prog = *progp;
    glAttachShader(prog, vertex_shader);
    glAttachShader(prog, fragment_shader);
    glLinkProgram(prog);

    int success;
    glGetProgramiv(prog, GL_LINK_STATUS, &success);
    if(!success) {
        char infoLog[512];
        glGetProgramInfoLog(prog, sizeof(infoLog), NULL, infoLog);
        printf("Error linking shaders: %s\n", infoLog);
        return false;
    }

    // Pode-se apagar os shaders depois de linkar se não forem mais usados
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return true;
}

void shaderSetFloat(unsigned int shader, const char* uniform, float val) {
    unsigned int loc = glGetUniformLocation(shader, uniform);
    glUniform1f(loc, val);
}

void shaderSetInt(unsigned int shader, const char* uniform, int val) {
    unsigned int loc = glGetUniformLocation(shader, uniform);
    glUniform1i(loc, val);
}

void shaderSetUint(unsigned int shader, const char* uniform, unsigned int val) {
    unsigned int loc = glGetUniformLocation(shader, uniform);
    glUniform1ui(loc, val);
}

void shaderSetBool(unsigned int shader, const char* uniform, bool val) {
    unsigned int loc = glGetUniformLocation(shader, uniform);
    glUniform1i(loc, val);
}


bool createTexture(unsigned int* texp, const char* tex_file, bool gen_mipmaps, bool flipv) {
    // Load file
    stbi_set_flip_vertically_on_load(flipv);
    int width, height, nrChannels;
    unsigned char* tex_data = stbi_load(tex_file, &width, &height, &nrChannels, 0);
    if (tex_data == NULL) {
        fprintf(stderr, "Couldn't load image \"%s\"\n", tex_file);
        return false;
    }

    glGenTextures(1, texp);

    unsigned int tex = *texp;
    glBindTexture(GL_TEXTURE_2D, tex);

    GLenum tex_format = nrChannels == 3 ? GL_RGB : GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, tex_format, GL_UNSIGNED_BYTE, tex_data);

    if (gen_mipmaps) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(tex_data);

    return true;
}

void textureSetFilter(unsigned int tex, GLint filterMin, GLint filterMag) {
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMag);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMin);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void textureSetWrap(unsigned int tex, GLint wrapS, GLint wrapT) {
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    glBindTexture(GL_TEXTURE_2D, 0);
}
