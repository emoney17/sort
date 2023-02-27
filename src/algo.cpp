#include "algo.h"

void Algo::print(std::vector<int> arr)
{
    for (auto i : arr) std::cout << i << " ";
    std::cout << std::endl;
}

std::vector<int> Algo::generateArray()
{
    std::vector<int> arr;
    srand(time(0));
    for (int i = 0; i < Size; i++)
    {
        int element = rand()%100;
        arr.push_back(element);
    }
    return arr;
}

void Algo::selectionSort()
{
    for (int i = 0; i < Size - 1; i++)
    {
        int min = i;
        for (int j = i+1; j < Size; j++)
        {
            if (Arr.at(min) > Arr.at(j))
                min = j;
        }
        if (min != i)
            std::swap(Arr.at(i), Arr.at(min));
        usleep(1000 * 1000);
        print(Arr);

    }
}
