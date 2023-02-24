#include "algo.h"

std::vector<int> Algo::generateArray()
{
    srand(time(0));
    std::cout << "Generating random array.." << std::endl;
    for (int i = 0; i < arrSize - 1; i++)
    {
        int element = rand()%100;
        std::cout << "Element: " << element << std::endl;
        arr.push_back(element);
    }
    return arr;
}

std::vector<int> Algo::selectionSort()
{

}
