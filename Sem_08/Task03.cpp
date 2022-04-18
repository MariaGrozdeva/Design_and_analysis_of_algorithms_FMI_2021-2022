#include <iostream>
#include <vector>
#include <algorithm>

int maxSum(const std::vector<int>& A, const std::vector<int>& B, const std::vector<int>& C)
{
	std::vector<std::vector<int>> maxSums;
	for (size_t i = 0; i < 3; i++)
		maxSums.push_back(std::vector<int>(2)); // We don't need to keep track of all n columns.
	                                            // We only need to keep the last two columns.
	                                            // Thus we optimise the spatial complexity from O(n) to O(1).

	maxSums[0][0] = A[0];
	maxSums[1][0] = B[0];
	maxSums[2][0] = C[0];

	for (size_t i = 1; i < A.size(); i++)
	{
		maxSums[0][1] = std::max(maxSums[1][0], maxSums[2][0]) + A[i];
		maxSums[1][1] = std::max(maxSums[0][0], maxSums[2][0]) + B[i];
		maxSums[2][1] = std::max(maxSums[0][0], maxSums[1][0]) + C[i];

		maxSums[0][0] = maxSums[0][1];
		maxSums[1][0] = maxSums[1][1];
		maxSums[2][0] = maxSums[2][1];
	}

	return std::max({ maxSums[0][1], maxSums[1][1], maxSums[2][1] });
}

int main()
{
	std::vector<int> A = { 2, 3, 5, 1, 8, 7, 6 };
	std::vector<int> B = { 6, 9, 8, 0, 5, 9, 7 };
	std::vector<int> C = { 4, 1, 2, 8, 4, 2, 5 };

	std::cout << "The maximal sum of n summands is " << maxSum(A, B, C) << '.' << std::endl;
}