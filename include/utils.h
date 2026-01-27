#ifndef UTILS_H
#define UTILS_H

#include "glad/glad.h"
#include <stdbool.h>

#define shaderSet(shader, uniform, val) _Generic( (val), float: shaderSetFloat, int: shaderSetInt, unsigned int: shaderSetUint, bool: shaderSetBool) (shader, uniform, val)

#ifdef __cplusplus
extern "C" {
#endif

// Criar program e linkar shaders nele
bool makeShaderProgram(unsigned int* progp, const char* vertex_code, const char* fragment_code);

void shaderSetFloat(unsigned int shader, const char* uniform, float val);
void shaderSetInt(unsigned int shader, const char* uniform, int val);
void shaderSetUint(unsigned int shader, const char* uniform, unsigned int val);
void shaderSetBool(unsigned int shader, const char* uniform, bool val);

// Textures
bool createTexture(unsigned int* texp, const char* tex_file, bool gen_mipmaps, bool flipv);
void textureSetFilter(unsigned int tex, GLint filterMin, GLint filterMag);
void textureSetWrap(unsigned int tex, GLint wrapS, GLint wrapT);

#ifdef __cplusplus
}
#endif

#endif