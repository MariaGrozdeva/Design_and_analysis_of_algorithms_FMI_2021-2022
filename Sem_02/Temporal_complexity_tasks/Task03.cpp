#include <iostream>

int f(int n)
{
	int curr = 0;
	for (size_t i = 0; i < n; i++)
		curr += 1;

	return curr % 2;
}

int f3(int n)
{
	int res = 1;
	for (size_t i = n; i >= 1; i /= 2)
		res = f(res);

	return res;
}

int main()
{
	std::cout << f3(30);
}