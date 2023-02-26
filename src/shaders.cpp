#include "shaders.h"

unsigned int Shader::readShaders()
{
    std::string vertexShaderCode, fragmentShaderCode;
    std::ifstream vertexShaderStream(VertexPath, std::ios::in);
    std::ifstream fragmentShaderStream(FragmentPath, std::ios::in);

    if (vertexShaderStream.is_open())
    {
        std::stringstream ss;
        ss << vertexShaderStream.rdbuf();
        vertexShaderCode = ss.str();
        vertexShaderStream.close();
    }
    else
    {
        std::cout << "ERROR::SHADER::VERTEX::READING FAILED: " << VertexPath << '\n';
        return -1;
    }

    if (fragmentShaderStream.is_open())
    {
        std::stringstream ss;
        ss << fragmentShaderStream.rdbuf();
        fragmentShaderCode = ss.str();
        fragmentShaderStream.close();
    }
    else
    {
        std::cout << "ERROR::SHADER::FRAGMENT::READING FAILED: " << FragmentPath << '\n';
        return -1;
    }

    // Create the shaders
    const char* vertexShaderSource = vertexShaderCode.c_str();
    const char* fragmentShaderSource = fragmentShaderCode.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    compileShaders(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    compileShaders(fragmentShader);

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    validateProgram(program);

    return program;
}

void Shader::compileShaders(unsigned int shader)
{
    int success;
    char infoLog[512];
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILE FAILED\n" << infoLog << std::endl;
    }

}

void Shader::validateProgram(unsigned int program)
{
    int success;
    char infoLog[512];
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR:SHADER::PROGRAM::LINKING FAILED\n" << infoLog << std::endl;
    }
}
