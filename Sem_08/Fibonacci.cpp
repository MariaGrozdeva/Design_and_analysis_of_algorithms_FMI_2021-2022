#include <iostream>
#include <vector>
#include <ctime>

size_t fibonacciRecursive(size_t n)
{
	if (n <= 1)
		return 1;

	return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

size_t fibonacciMemoization(size_t n, std::vector<size_t>& mem)
{
	if (n <= 1)
		return 1;

	if (mem[n] != 0)
		return mem[n];

	size_t currentFib = fibonacciMemoization(n - 1, mem) + fibonacciMemoization(n - 2, mem);
	mem[n] = currentFib;

	return currentFib;
}
size_t fibonacciMemoization(size_t n)
{
	std::vector<size_t> mem(n + 1, 0);
	return fibonacciMemoization(n, mem);
}

size_t fibonacciDP(size_t n)
{
	std::vector<size_t> fibNums(3); // We need to keep track only of the last two fibonacci numbers and the current one.

	fibNums[0] = fibNums[1] = 1;

	for (size_t i = 2; i <= n; i++)
	{
		fibNums[2] = fibNums[1] + fibNums[0];
		fibNums[0] = fibNums[1];
		fibNums[1] = fibNums[2];
	}

	return fibNums[2];
}

int main()
{
	time_t start, end;

	std::cout << "Fibonacci recursive...";
	start = std::time(NULL);
	fibonacciRecursive(45);
	end = std::time(NULL);
	std::cout << "\n    execution took " << end - start << " second(s)\n\n";

	std::cout << "Fibonacci with memoization...";
	start = std::time(NULL);
	fibonacciMemoization(45);
	end = std::time(NULL);
	std::cout << "\n    execution took " << end - start << " second(s)\n\n";

	std::cout << "Fibonacci with dynamic programming...";
	start = std::time(NULL);
	fibonacciDP(45);
	end = std::time(NULL);
	std::cout << "\n    execution took " << end - start << " second(s)\n\n";
}