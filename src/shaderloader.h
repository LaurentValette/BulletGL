#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <iostream>
#include <fstream>

#define GLEW_STATIC
#include <GL/glew.h>

namespace ShaderLoader {
    std::string readFile(const char* filePath);
    void attachShader(const char* file_path, GLenum shader_type, GLuint program);
}

#endif // SHADERLOADER_H
