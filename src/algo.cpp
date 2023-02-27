#include "algo.h"

void Algo::print(std::vector<int> arr)
{
    for (auto i : arr) std::cout << i << " ";
    std::cout << std::endl;
}

std::vector<int> Algo::selectionSort()
{
    int vecSize = sort.size();
    for (int i = 0; i < vecSize - 1; i++)
    {
        int min = i;
        for (int j = i+1; j < vecSize; j++)
        {
            if (sort.at(min) > sort.at(j))
                min = j;
        }
        if (min != i)
            std::swap(sort.at(i), sort.at(min));
        usleep(1000 * 1000);
        print(sort);
    }
    return(sort);
}
