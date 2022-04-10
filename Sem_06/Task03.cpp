#include <iostream>
#include <algorithm>
#include <vector>

void print(double x, double y, double z)
{
	std::cout << "The sides of the triangle are of length: " << x << ", " << y << ", " << z << std::endl;
}

bool formATriangle(std::vector<double> arr)
{
	std::make_heap(arr.begin(), arr.end());
	std::sort_heap(arr.begin(), arr.end());

	for (size_t i = 0; i < arr.size() - 2; i++)
	{
		if (arr[i] + arr[i + 1] > arr[i + 2])
		{
			print(arr[i], arr[i + 1], arr[i + 2]);
			return true;
		}
	}

	return false;
}

int main()
{
	std::vector<double> arr = { 2.5, 1, 11, 3.6, 8 };
	if (!formATriangle(arr))
		std::cout << "No such triangle!" << std::endl;
}