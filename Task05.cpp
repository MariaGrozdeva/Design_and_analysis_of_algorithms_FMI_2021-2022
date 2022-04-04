#include <iostream>
#include <vector>

template <class T>
size_t partition(T* arr, size_t len, T p)
{
	T pivot = p;
	size_t i = 0, j = len - 1;

	while (true)
	{
		while (arr[j] > pivot)
			j--;

		while (arr[i] < pivot)
			i++;

		if (i < j)
			std::swap(arr[i], arr[j]);
		else
			return j;
	}
}

void rearrange(std::vector<int>& v)
{
	size_t p = partition(v.data(), v.size(), 0) + 1; // p holds the index of the first positive element

	for (size_t i = 0; p < v.size() && i < p; p++, i += 2)
		std::swap(v[i], v[p]);
}

int main()
{
	std::vector<int> v = { 9, -3, 5, -2, -8, -6, 1, 3 };
	rearrange(v);

	for (size_t i = 0; i < v.size(); i++)
		std::cout << v[i] << ' ';
}