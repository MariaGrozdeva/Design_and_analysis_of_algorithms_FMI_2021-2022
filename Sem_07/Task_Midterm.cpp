#include <iostream>
#include <vector>

void preprocess(const std::vector<size_t>& data, std::vector<size_t>& enumerativeArray, size_t lowerBound, size_t upperBound)
{
	size_t range = upperBound - lowerBound + 1;
	enumerativeArray.resize(range, 0);

	for (size_t i = 0; i < data.size(); i++)
		enumerativeArray[data[i] - lowerBound]++;

	for (size_t i = 0; i < enumerativeArray.size() - 1; i++)
		enumerativeArray[i + 1] += enumerativeArray[i];

}
size_t getLengthOfAnInterval(const std::vector<size_t>& queriesArray, size_t a, size_t b, size_t lowerBound)
{
	return queriesArray[b - lowerBound] - queriesArray[a - lowerBound] + 1;
}

int main()
{
	size_t l = 5; // lower bound of Ynumbers
	size_t m = 100; // upper bound of Ynumbers
	std::vector<size_t> Ynumbers = { 5, 8, 10, 22, 24, 23, 55, 66, 18 }; // n numbers

	std::vector<size_t> queriesArray;
	preprocess(Ynumbers, queriesArray, l, m); // Complexity: O(n+(m-l))

	size_t a, b;
	while (true)
	{
		std::cout << "Enter a and b:" << std::endl;
		std::cin >> a >> b;

		// Complexity: O(1) for each query
		std::cout << "There are " << getLengthOfAnInterval(queriesArray, a, b, l) << " numbers in the interval [" << a << ", " << b << "]." << std::endl << std::endl;
	}
}