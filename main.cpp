#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// TODO: Make this a mutable variable
const int width = 1200;
const int height = 800;
const char* title = "SORT VISUALIZER";
const char* fPath = "shader.frag";
const char* vPath = "shader.vert";

// Class to create shaders
// Class to create the window

void processKeys(GLFWwindow* window);
std::vector<glm::vec3> createBars(float size, int arr[]);

int main()
{
    // Window
    glfwInit();
    if (!glfwInit())
    {
	    std::cout << "ERROR::INIT::GLFW" << std::endl;
	    return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
	    std::cout << "ERROR::WINDOW::CREATION" << std::endl;
	    glfwTerminate();
	    return -1;
    }

    glfwMakeContextCurrent(window);

    glewInit();
    if (glewInit() != GLEW_OK)
    {
	    std::cout << "ERROR::INIT::GLEW" << std::endl;
	    return -1;
    }

    // Read shaders from file
    std::string vertexShaderCode;
    std::ifstream vertexShaderStream(vPath, std::ios::in);
    if (vertexShaderStream.is_open())
    {
        std::stringstream ss;
        ss << vertexShaderStream.rdbuf();
        vertexShaderCode = ss.str();
        vertexShaderStream.close();
    }
    else
    {
        std::cout << "ERROR::SHADER::VERTEX::READING FAILED: " << vPath << '\n';
        return -1;
    }

    std::string fragmentShaderCode;
    std::ifstream fragmentShaderStream(fPath, std::ios::in);
    if (fragmentShaderStream.is_open())
    {
        std::stringstream ss;
        ss << fragmentShaderStream.rdbuf();
        fragmentShaderCode = ss.str();
        fragmentShaderStream.close();
    }
    else
    {
        std::cout << "ERROR::SHADER::FRAGMENT::READING FAILED: " << fPath << '\n';
        return -1;
    }

    const char* vertexShaderSource = vertexShaderCode.c_str();
    const char* fragmentShaderSource = fragmentShaderCode.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILE FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILE FAILED\n" << infoLog << std::endl;
    }

    unsigned int programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        std::cout << "ERROR:SHADER::PROGRAM::LINKING FAILED\n" << infoLog << std::endl;
    }

    int algoArr[] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    };

    int bars = sizeof(algoArr) / sizeof(int);
    std::vector<glm::vec3> vertices = createBars(bars, algoArr);
    int numVert = 18 * bars;

    // Buffers
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
	    processKeys(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(programID);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, numVert);

	    glfwSwapBuffers(window);
	    glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(programID);
    glfwTerminate();
    return 0;
}

void processKeys(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	glfwSetWindowShouldClose(window, true);
}

// TODO: Function to generate verticies for bars
std::vector<glm::vec3> createBars(float size, int arr[])
{
    std::vector<glm::vec3> vertices;
    for (int i = 0; i < size; i++)
    {
        float leftdir = (0.0197 * i);
        float scale = (arr[i] / 10.0f);
        std::cout << "I: " << i << std::endl;
        std::cout << "ARR: " << arr[i] << std::endl;
        std::cout << "ZERO: " << (1.0f - (0.2f * i)) << std::endl;
        std::cout << "ONE: " << (1.0f - (0.2f * i)) << std::endl;
        std::cout << "TWO: " << (0.9f - (0.2f * i)) << std::endl;
        std::cout << "THREE: " << (0.9f - (0.2f * i)) << std::endl;

        // TODO: Zero y and Three y need to change based on array
        glm::vec3 zero (1.0f-leftdir, -0.9f + scale, 0.f);
        glm::vec3 one  (1.0f-leftdir, -1.0f, 0.f);
        glm::vec3 two  (0.989f-leftdir, -1.0f, 0.f);
        glm::vec3 three(0.989f-leftdir, -0.9f + scale, 0.f);

        vertices.push_back(zero);
        vertices.push_back(one);
        vertices.push_back(two);
        vertices.push_back(zero);
        vertices.push_back(two);
        vertices.push_back(three);
    }
    return vertices;
}
