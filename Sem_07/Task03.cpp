#include <iostream>
#include <vector>
#include <algorithm>

size_t getMinimumOperations(size_t n)
{
	std::vector<size_t> minOperations(n + 1, SIZE_MAX);

	minOperations[1] = 0;
	minOperations[2] = 1;
	minOperations[3] = 1;

	for (size_t i = 4; i <= n; i++)
	{
		size_t v1 = SIZE_MAX;
		size_t v2 = SIZE_MAX;
		size_t v3 = SIZE_MAX;

		if (i % 3 == 0)
			v1 = minOperations[i / 3];

		if (i % 2 == 0)
			v2 = minOperations[i / 2];

		v3 = minOperations[i - 1];
		
		minOperations[i] = 1 + std::min({ v1, v2, v3 });
	}

	return minOperations[n];
}

int main()
{
	std::cout << "The minimum number of operations is " << getMinimumOperations(962340) << std::endl;
}