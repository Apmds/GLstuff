#ifndef SHADERS_H
#define SHADERS_H

const char* vertex_shader_code = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "in vec3 color;\n"
    "out vec3 Color;\n"
    "void main() {\n"
    "   Color = color;\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n"
;

const char* fragment_shader_code = "#version 330 core\n"
    "in vec3 Color;\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "   FragColor = vec4(Color, 1.0f);\n"
    "}\n"
;


#endif