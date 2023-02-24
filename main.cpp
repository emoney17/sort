#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaders.h"
#include "window.h"
#include "algo.h"

void processKeys(GLFWwindow* window);
std::vector<glm::vec3> createBars(float size, std::vector<int> arr);

int main()
{
    // Window and library inits
    Window myWindow;
    myWindow.glfwStart();
    myWindow.Width = 800;
    myWindow.Height = 600;
    myWindow.Title = "SORT VISUALIZER";
    GLFWwindow* window = myWindow.createWindow();
    myWindow.windowContext(window);
    myWindow.glewStart();

    // Read shaders and create program
    Shader myShader;
    myShader.VertexPath = "./simple.vert";
    myShader.FragmentPath = "./simple.frag";
    unsigned int programID = myShader.readShaders();
    myShader.validateProgram(programID);

    // std::vector<int> algoArr = {
    //     1, 2, 3, 4, 5, 6, 7, 8, 9, 100,
    //     1, 2, 3, 4, 5, 6, 7, 8, 9, 100,
    //     1, 2, 3, 4, 5, 6, 7, 8, 9, 100,
    //     1, 2, 3, 4, 5, 6, 7, 8, 9, 100,
    //     1, 2, 3, 4, 5, 6, 7, 8, 9, 100,
    //     1, 2, 3, 4, 5, 6, 7, 8, 9, 100,
    //     1, 2, 3, 4, 5, 6, 7, 8, 9, 100,
    //     1, 2, 3, 4, 5, 6, 7, 8, 9, 100,
    //     1, 2, 3, 4, 5, 6, 7, 8, 9, 100,
    //     1, 2, 3, 4, 5, 6, 7, 8, 9, 100
    // };

    Algo myAlgo;
    myAlgo.arrSize = 100;
    std::vector<int> algoArr = myAlgo.generateArray();

    int bars = algoArr.size();
    std::vector<glm::vec3> vertices = createBars(bars, algoArr);
    int numVert = 18 * bars;

    // Buffers and creen loop
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
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
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

std::vector<glm::vec3> createBars(float size, std::vector<int> arr)
{
    std::vector<glm::vec3> vertices;
    for (int i = 0; i < size; i++)
    {
        float leftdir = (0.0197 * i);
        float scale = (arr[i] / 55.0f);

        glm::vec3 zero ((1.0f  - leftdir), (-0.9f + scale), 0.f); // 0
        glm::vec3 one  ((1.0f  - leftdir), (-1.0f),         0.f); // 1
        glm::vec3 two  ((0.989f- leftdir), (-1.0f),         0.f); // 2
        glm::vec3 three((0.989f- leftdir), (-0.9f + scale), 0.f); // 3

        vertices.push_back(zero);
        vertices.push_back(one);
        vertices.push_back(two);
        vertices.push_back(zero);
        vertices.push_back(two);
        vertices.push_back(three);
    }
    return vertices;
}
