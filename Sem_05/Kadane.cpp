#include <iostream>
#include <vector>

size_t kadane(const std::vector<int>& arr) // Maximum subarray problem
{
	int m = 0; // Максималната сума на подмасив, завършващ на arr[0], arr[1],.., arr[i-1].
	int l = 0; // Максималната сума на подмасив, завършващ на arr[i-1].

	for (size_t i = 0; i < arr.size(); i++)
	{
		l += arr[i];

		if (l < 0)
			l = 0;

		if (l > m)
			m = l;
	}
	return m;
}
int main()
{
	std::vector<int> v = { -5,-24,22,-3,23 };

	std::cout << kadane(v);
}