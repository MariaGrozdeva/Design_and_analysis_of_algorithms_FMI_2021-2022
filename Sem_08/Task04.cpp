#include <iostream>
#include <vector>

void printTable(const std::vector<std::vector<size_t>>& dyn)
{
	std::cout << "Dynamic programming table:" << std::endl;
	for (size_t i = 0; i < dyn.size(); i++)
	{
		for (size_t j = 0; j < dyn[0].size(); j++)
			std::cout << dyn[i][j] << ' ';
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

size_t solutionsEquation(const std::vector<size_t>& A, size_t B)
{
	std::vector<std::vector<size_t>> dyn(A.size() + 1); // Memory optimisation is to keep only the last two rows.
	                                                    // Here is not done in order to print the dynamic table.
	for (size_t i = 0; i < dyn.size(); i++)
		dyn[i].resize(B + 1, 0);

	for (size_t i = 0; i < dyn.size(); i++)
		dyn[i][0] = 1;

	for (size_t i = 1; i < dyn.size(); i++)
	{
		for (size_t B = 1; B < dyn[0].size(); B++)
		{
			if (A[i - 1] > B)
				dyn[i][B] = dyn[i - 1][B];
			else
				dyn[i][B] = dyn[i - 1][B] + dyn[i][B - A[i - 1]];
		}
	}

	printTable(dyn);
	return dyn[dyn.size() - 1][dyn[0].size() - 1];
}

int main()
{
	std::vector<size_t> A = { 2, 3, 5 };
	size_t B = 9;

	std::cout << "The solution is " << solutionsEquation(A, B) << '.' << std::endl;
}