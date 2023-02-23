#include "window.h"

GLFWwindow* Window::createWindow()
{
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(Width, Height, Title, NULL, NULL);
    if (window == NULL)
    {
	    std::cout << "ERROR::WINDOW::CREATION" << std::endl;
	    glfwTerminate();
    }
    return window;
}

void Window::windowContext(GLFWwindow * window)
{
    glfwMakeContextCurrent(window);
}

void Window::glfwStart()
{
    glfwInit();
    if (!glfwInit())
    {
	    std::cout << "ERROR::INIT::GLFW" << std::endl;
	    return;
    }
}

void Window::glewStart()
{
    glewInit();
    if (glewInit() != GLEW_OK)
    {
	    std::cout << "ERROR::INIT::GLEW" << std::endl;
	    return;
    }
}
