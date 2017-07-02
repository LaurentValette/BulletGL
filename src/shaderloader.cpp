#include "shaderloader.h"

std::string ShaderLoader::readFile(const char* filePath)
{
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if(!fileStream.is_open())
    {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while (!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

void ShaderLoader::attachShader(const char *file_path, GLenum shader_type, GLuint program)
{
    std::string src = readFile(file_path);
    const char* src_cstr = src.c_str();

    GLuint shader_ref = glCreateShader(shader_type);
    glShaderSource(shader_ref, 1, &src_cstr, NULL);
    glCompileShader(shader_ref);

    // Check compilation status and dump detailled logs
    GLint shader_status;
    glGetObjectParameterivARB(shader_ref, GL_COMPILE_STATUS, &shader_status);
    if (shader_status)
    {
        std::cout << "Shader compiled successfully" << std::endl;

        glAttachShader(program, shader_ref);
    }
    else
    {
        std::cerr << "Shader failed to compile" << std::endl;

        GLint buffer_len = 0;
        glGetShaderiv(shader_ref, GL_INFO_LOG_LENGTH , &buffer_len);
        if (buffer_len > 1)
        {
            GLchar* compiler_log = (GLchar*) malloc(buffer_len);

            GLsizei slen = 0;
            glGetInfoLogARB(shader_ref, buffer_len, &slen, compiler_log);
            std::cerr << compiler_log << std::endl;
            free(compiler_log);
        }
    }

    glDeleteShader(shader_ref);
}
