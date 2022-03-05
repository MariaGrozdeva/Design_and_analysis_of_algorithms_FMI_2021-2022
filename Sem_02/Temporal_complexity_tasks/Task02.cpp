#include <iostream>

int f2(int n)
{
	int res = 0;
	for (size_t i = 1; i <= n; i *= 2)
	{
		for (size_t j = 1; j <= i; j++)
			res++;		
	}

	return res;
}

int main()
{
	std::cout << f2(29);
}