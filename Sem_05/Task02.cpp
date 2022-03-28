#include <iostream>
#include "Pick.hpp"

template <typename T>
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

size_t countSouvenirsICanBuy(size_t* souvenirs, size_t len, size_t money)
{
	if (len == 0)
		return 0;

	if (len == 1)
		return souvenirs[0] <= money;

	size_t mid = len / 2;

	size_t median = PICK<size_t>(souvenirs, len, mid); // O(n)

	partition<size_t>(souvenirs, len, median); // O(n)

	size_t sum = 0;
	for (size_t i = 0; i < mid; i++) // O(n)
		sum += souvenirs[i];

	if (sum == money)
		return mid;

	if (sum > money)
		return countSouvenirsICanBuy(souvenirs, mid, money);

	if (sum < money)
		return mid + countSouvenirsICanBuy(souvenirs + mid, len - mid, money - sum);
}
int main()
{
	size_t souvenirs[] = { 39, 4, 6, 1, 2, 66, 33 };

	std::cout << countSouvenirsICanBuy(souvenirs, sizeof(souvenirs) / sizeof(size_t), 40);
}
