#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
    public:
        int Width;
        int Height;
        const char* Title;

        GLFWwindow* createWindow();
        void windowContext(GLFWwindow*);
        void glfwStart();
        void glewStart();
};
