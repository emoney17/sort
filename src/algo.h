#include <iostream>
#include <vector>
#include <unistd.h>

class Algo
{
    public:
        int arraySize;
        std::vector<int> sort;

        void print(std::vector<int> arr);
        std::vector<int> selectionSort();
};
