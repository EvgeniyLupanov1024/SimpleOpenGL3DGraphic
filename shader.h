#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

using namespace std;

class Shader
{
    public:
        GLuint Program;

        Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
        void use();

    private:
        GLuint compileShader(const GLchar* shaderCode, GLuint shaderType);
        const GLchar* shaderFileToStr(const GLchar* shaderPath);
        void linkShaderProgram();
};

#endif