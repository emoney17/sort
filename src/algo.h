#include <iostream>
#include <vector>
#include <unistd.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Algo
{
    public:
        int Size = 100;
        unsigned int Time;
        std::vector<int> Arr;
        int numVert = 18 * Size;

        std::vector<int> generateArray();
        void print(std::vector<int> arr);
        void selectionSort(GLFWwindow* window, unsigned int VAO, unsigned int VBO);
        std::vector<glm::vec3> createBars();
};
