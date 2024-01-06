#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

unsigned getMinimumOperations(unsigned n)
{
	std::vector<unsigned> minOperations(n + 1, UINT_MAX);

	minOperations[1] = 0;
	minOperations[2] = 1;
	minOperations[3] = 1;

	for (size_t i = 4; i <= n; i++)
	{
		unsigned int v1 = i % 3 == 0 ? minOperations[i / 3] : UINT_MAX;
    		unsigned int v2 = i % 2 == 0 ? minOperations[i / 2] : UINT_MAX;
    		unsigned int v3 = minOperations[i - 1];

		minOperations[i] = 1 + std::min({ v1, v2, v3 });
	}

	return minOperations[n];
}

int main()
{
	std::cout << "The minimum number of operations is " << getMinimumOperations(962340) << std::endl;
}
