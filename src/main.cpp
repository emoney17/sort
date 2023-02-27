#include <iostream>
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
    Window myWindow;
    myWindow.glfwStart();
    myWindow.Width = 800;
    myWindow.Height = 600;
    myWindow.Title = "SORT VISUALIZER";
    GLFWwindow* window = myWindow.createWindow();
    myWindow.windowContext(window);
    myWindow.glewStart();

    Shader myShader;
    myShader.VertexPath = "./shaders/simple.vert";
    myShader.FragmentPath = "./shaders/simple.frag";
    unsigned int programID = myShader.readShaders();
    myShader.validateProgram(programID);

    Algo myAlgo;
    myAlgo.Size = 100;
    myAlgo.Arr = myAlgo.generateArray();
    int numVert = 18 * myAlgo.Size;
    std::vector<glm::vec3> vertices = createBars(myAlgo.Size, myAlgo.Arr);

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
        glUseProgram(programID);

        for (int i = 0; i < myAlgo.Size - 1; i++)
        {
            int min = i;
            for (int j = i+1; j < myAlgo.Size; j++)
            {
                if (myAlgo.Arr.at(min) > myAlgo.Arr.at(j))
                    min = j;
            }
            if (min != i)
            {
                std::swap(myAlgo.Arr.at(i), myAlgo.Arr.at(min));
                usleep(1000 * 100);
                // myAlgo.print(myAlgo.Arr);
                std::vector<glm::vec3> sortedVerticies = createBars(myAlgo.Size, myAlgo.Arr);
                glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glBindBuffer(GL_ARRAY_BUFFER, VBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * sortedVerticies.size(), &sortedVerticies[0], GL_STATIC_DRAW);
                glBindVertexArray(VAO);
                glDrawArrays(GL_TRIANGLES, 0, numVert);
                glfwSwapBuffers(window);
                glfwPollEvents();
            }
        }

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
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	glfwSetWindowShouldClose(window, true);
}

std::vector<glm::vec3> createBars(float size, std::vector<int> arr)
{
    std::vector<glm::vec3> vertices;
    for (int i = 0; i < size; i++)
    {
        float leftdir = (0.0197 * i);
        float scale = (arr[i] / 55.0f);

        glm::vec3 zero((1.0f - leftdir), (-0.9f + scale), 0.f); // 0
        glm::vec3 one((1.0f - leftdir), (-1.0f), 0.f); // 1
        glm::vec3 two((0.989f- leftdir), (-1.0f), 0.f); // 2
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
