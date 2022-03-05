#include <iostream>

int f1(int n)
{
	int res = 1;
	for (size_t i = 1; i <= n; i++)
	{
		for (size_t j = 1; j <= i * i; j++)
			res++;
	}
	
	for (size_t i = 0; i < 1000000; i++)
	{
		if (res % 3 == 0)
			res /= 3;
		else
			res *= 3;
	}
	
	return res;
}

int main()
{
	std::cout << f1(22);
}