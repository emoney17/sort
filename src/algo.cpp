#include "algo.h"

void Algo::print(std::vector<int> arraySorted)
{
    for (auto i : arraySorted) std::cout << i << " ";
    std::cout << std::endl;
}

std::vector<int> Algo::generateArray()
{
    srand(time(0));
    for (int i = 0; i < arrSize - 1; i++)
    {
        int element = rand()%arrSize;
        arr.push_back(element);
    }
    print(arr);
    return arr;
}

std::vector<int> Algo::selectionSort(std::vector<int> arr)
{
    int temp;
    std::vector<int> sort = arr;
    int vecsize = sort.size();
    for (int i = 0; i < vecsize - 1; i++)
    {
        int min = i;
        for (int j = i+1; j < vecsize; j++)
        {
            if (sort.at(min) > sort.at(j))
                min = j;
        }
        if (min != i)
        {
           std::swap(sort.at(i), sort.at(min));
        }
        return sort;
    }
}
