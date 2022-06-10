#include "shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
    GLuint vertexShader = compileShader(vertexPath, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentPath, GL_FRAGMENT_SHADER);

    Program = glCreateProgram();
    glAttachShader(Program, vertexShader);
    glAttachShader(Program, fragmentShader);

    linkShaderProgram();
}

GLuint Shader::compileShader(const GLchar* shaderPath, GLuint shaderType)
{
    const GLchar* shaderCode = shaderFileToStr(shaderPath);
    
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << endl;
        throw runtime_error (infoLog);
    };

    return shader;
}

const GLchar* Shader::shaderFileToStr(const GLchar* shaderPath)
{
    ifstream shaderFile;
    stringstream shaderStream;

    try 
    {
        shaderFile.open(shaderPath, ios::in);
        shaderStream << shaderFile.rdbuf();
        string *code = new string(shaderStream.str());
        shaderFile.close();

        return code->c_str();
    }
    catch (ifstream::failure e)
    {
        throw e;
    }
}

void Shader::linkShaderProgram()
{
    glLinkProgram(Program);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(Program, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(Program, 512, NULL, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << endl;
        throw runtime_error (infoLog);
    };
}

void Shader::use()
{
    glUseProgram(this->Program);
}
