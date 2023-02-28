#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader
{
    public:
        const char* VertexPath;
        const char* FragmentPath;

        unsigned int readShaders();
        void compileShaders(unsigned int shader);
        void validateProgram(unsigned int program);
};
