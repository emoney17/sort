#include <iostream>
#include <vector>

class Algo
{
    public:
        int choice = 1;
        int arrSize;
        std::vector<int> arr;

        std::vector<int> generateArray();
        std::vector<int> selectionSort();
};
