#include <iostream>
#include <vector>
#include <algorithm>

size_t theft(const std::vector<size_t>& paintingsPrices)
{
	std::vector<size_t> maxProfits(3); // We don't need to keep track of all n max profits. 
	                                   // We only need to keep the last three elements (maxProfits[k-2], maxProfits[k-1], maxProfits[k]).
	                                   // Thus we optimise the spatial complexity from O(n) to O(1).

	maxProfits[0] = paintingsPrices[0];
	maxProfits[1] = std::max(maxProfits[0], maxProfits[1]);

	for (size_t i = 2; i < paintingsPrices.size(); i++)
	{
		maxProfits[2] = std::max(paintingsPrices[i] + maxProfits[0], maxProfits[1]);
		maxProfits[0] = maxProfits[1];
		maxProfits[1] = maxProfits[2];
	}

	return maxProfits[2];
}

int main()
{
	std::vector<size_t> paintingsPrices = { 7, 6, 13, 20, 1, 18, 19 };
	std::cout << "The most expensive collection the thief can steal costs " << theft(paintingsPrices) << '.' << std::endl;
}