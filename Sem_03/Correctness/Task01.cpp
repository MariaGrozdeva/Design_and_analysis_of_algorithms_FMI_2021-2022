#include <iostream>

size_t mystery(size_t x, size_t y)
{
	size_t z = x;
	size_t t = y;
	size_t p = 1;

	while (t > 0)
	{
		if (t % 2 == 0)
		{
			z = z * z;
			t = t / 2;
		}
		else
		{
			p = p * z;
			t = t - 1;
		}
	}
	return p;
}

int main()
{
	std::cout << mystery(6, 9);
}