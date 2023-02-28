#include <iostream>
#include <unistd.h>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaders.h"
#include "window.h"
#include "algo.h"

void processKeys(GLFWwindow* window, unsigned int VAO, unsigned int VBO, Algo myAlgo);
void drawArr(unsigned int VAO, unsigned int VBO, std::vector<glm::vec3> verticies, int numVert);

int main()
{
    Window myWindow;
    myWindow.glfwStart();
    myWindow.Width = 800;
    myWindow.Height = 600;
    myWindow.Title = "SORT VISUALIZER";
    GLFWwindow* window = myWindow.createWindow();
    myWindow.windowContext(window);
    myWindow.glewStart();

    Shader myShader;
    myShader.VertexPath = "./simple.vert";
    myShader.FragmentPath = "./simple.frag";
    unsigned int programID = myShader.readShaders();
    myShader.validateProgram(programID);

    Algo myAlgo;
    myAlgo.Size = 100;
    myAlgo.Arr = myAlgo.generateArray();
    myAlgo.Time = 1000 * 80;
    std::vector<glm::vec3> vertices = myAlgo.createBars();

    unsigned int VBO, VAO;
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // drawArr(VAO, VBO, vertices, numVert);

	processKeys(window, VAO, VBO, myAlgo);
        glUseProgram(programID);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(programID);
    glfwTerminate();
    return 0;
}

void drawArr(unsigned int VAO, unsigned int VBO, std::vector<glm::vec3> vertices, int numVert)
{
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, numVert);
}

void processKeys(GLFWwindow* window, unsigned int VAO, unsigned int VBO, Algo myAlgo)
{
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    	glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        myAlgo.selectionSort(window, VAO, VBO);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        myAlgo.bubbleSort(window, VAO, VBO);
}
