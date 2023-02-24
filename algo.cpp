#include "algo.h"

void Algo::generateArray()
{
    srand(time(0));
    std::cout << "Generating random array.." << std::endl;
    for (int i = 0; i < arrSize; i++)
    {
        int element = rand()%20;
        arr.push_back(element);
    }
}
