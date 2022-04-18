#include <iostream>
#include <vector>
#include <algorithm>

void printSolution(const std::vector<size_t>& paintingPrices, const std::vector<size_t>& maxProfits)
{
	std::vector<size_t> solution;
	int i = maxProfits.size() - 1;

	while (i >= 0)
	{
		if (i == 0)
		{
			solution.push_back(paintingPrices[0]);
			i--;
		}
		else if (maxProfits[i] == maxProfits[i - 1])
		{
			i--;
		}
		else
		{
			solution.push_back(paintingPrices[i]);
			i -= 2;
		}
	}

	std::cout << "The solution is: ";
	for (int i = solution.size() - 1; i >= 0; i--)
		std::cout << solution[i] << ' ';
	std::cout << std::endl;
}

size_t theft(const std::vector<size_t>& paintingsPrices)
{
	std::vector<size_t> maxProfits(paintingsPrices.size()); // We don't need to keep track of all n max profits. 
															// We only need to keep the last three elements (maxProfits[k-2], maxProfits[k-1], maxProfits[k]).
															// Thus we optimise the spatial complexity from O(n) to O(1).

	maxProfits[0] = paintingsPrices[0];
	maxProfits[1] = std::max(maxProfits[0], maxProfits[1]);

	for (size_t i = 2; i < paintingsPrices.size(); i++)
		maxProfits[i] = std::max(paintingsPrices[i] + maxProfits[i - 2], maxProfits[i - 1]);

	printSolution(paintingsPrices, maxProfits);
	return maxProfits[paintingsPrices.size() - 1];
}

int main()
{
	std::vector<size_t> paintingsPrices = { 7, 8, 13, 20, 1, 18, 19 };
	std::cout << "The most expensive collection the thief can steal costs " << theft(paintingsPrices) << '.' << std::endl;
}