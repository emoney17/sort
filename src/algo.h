#include <iostream>
#include <vector>
#include <unistd.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Algo
{
    public:
        int Size;
        std::vector<int> Arr;

        std::vector<int> generateArray();
        void print(std::vector<int> arr);
        void selectionSort();
        std::vector<int> createBars();
};
