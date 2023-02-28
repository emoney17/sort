#include "algo.h"
#include <GLFW/glfw3.h>

void Algo::print(std::vector<int> arr)
{
    for (auto i : arr) std::cout << i << " ";
    std::cout << std::endl;
}

std::vector<int> Algo::generateArray()
{
    std::vector<int> arr;
    srand(time(0));
    for (int i = 0; i < Size; i++) {
        int element = rand()%100;
        arr.push_back(element);
    }
    return arr;
}

void Algo::selectionSort(GLFWwindow* window, unsigned int VAO, unsigned int VBO)
{
    std::vector<glm::vec3> vertices = createBars();

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

    for (int i = 0; i < Size - 1; i++) {
        int min = i;
        for (int j = i+1; j < Size; j++) {
            if (Arr.at(min) > Arr.at(j))
                min = j;
        }
        if (min != i) {
            std::swap(Arr.at(i), Arr.at(min));
            usleep(Time);

            std::vector<glm::vec3> sortedVerticies = createBars();

            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * sortedVerticies.size(),
			 &sortedVerticies[0], GL_STATIC_DRAW);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, numVert);
            glfwSwapBuffers(window);
        }
    }
}

void Algo::bubbleSort(GLFWwindow* window, unsigned int VAO, unsigned int VBO)
{
    std::vector<glm::vec3> vertices = createBars();

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

    for (int i = 0; i < Size - 1; i++) {
	for (int j = 0; j < Size - 1; j++) {
	    if (Arr[j] > Arr[j + 1]) {
		std::swap(Arr[j], Arr[j + 1]);
		//usleep(Time);
		std::vector<glm::vec3> sortedVerticies = createBars();
		
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * sortedVerticies.size(),
			     &sortedVerticies[0], GL_STATIC_DRAW);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, numVert);
		glfwSwapBuffers(window);
	    }
	}
    }
}

std::vector<glm::vec3> Algo::createBars()
{
    std::vector<glm::vec3> vertices;
    for (int i = 0; i < Size; i++) {
        float leftdir = (0.0197 * i);
        float scale = (Arr[i] / 55.0f);

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
