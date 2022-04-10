#include <iostream>
#include <algorithm>
#include <vector>

void printPair(int x, int y)
{
    std::cout << "Pair found (" << x << ", " << y << ')' << std::endl;
}

bool findPair(std::vector<int>& arr, int K)
{
    std::make_heap(arr.begin(), arr.end());
    std::sort_heap(arr.begin(), arr.end());

    size_t l = 0, h = arr.size() - 1;

    while (l < h)
    {
        if (arr[l] + arr[h] == K)
        {
            printPair(arr[l], arr[h]);
            return true;
        }

        (arr[l] + arr[h] < K) ? l++ : h--;
    }

    return false;
}

int main()
{
    std::vector<int> arr = { 8, 7, 2, 5, 3, 1 };
    if (!findPair(arr, 10))
        std::cout << "No such pair!" << std::endl;
}