#include <iostream>

bool isPrime(unsigned n)
{
	if (n <= 1)
		return false;

	unsigned temp = sqrt(n);
	for (size_t i = 2; i <= temp; i++)
	{
		if (n % i == 0)
			return false;
	}
	return true;
}

int main()
{
	std::cout << isPrime(37);
}