#include <iostream>
#include <vector>
#include <algorithm>

template <class T>
void merge(T* arr1, size_t len1, T* arr2, size_t len2, T* res)
{
	T* result = new T[len1 + len2];

	size_t cursor1 = 0;
	size_t cursor2 = 0;
	size_t resultCursor = 0;

	while (cursor1 < len1 && cursor2 < len2)
	{
		if (arr1[cursor1] < arr2[cursor2])
			result[resultCursor++] = arr1[cursor1++];
		else
			result[resultCursor++] = arr2[cursor2++];
	}

	while (cursor1 < len1)
		result[resultCursor++] = arr1[cursor1++];
	while (cursor2 < len2)
		result[resultCursor++] = arr2[cursor2++];

	for (size_t i = 0; i < len1 + len2; i++)
		res[i] = result[i];

	delete[] result;
}

void sortSpecialArray(std::vector<int>& arr)
{
	std::vector<int> even;
	std::vector<int> odd;

	for (size_t i = 0; i < arr.size(); i++)
	{
		if (arr[i] % 2 == 0)
			even.push_back(arr[i]);
		else
			odd.push_back(arr[i]);
	}

	std::reverse(odd.begin(), odd.end());
	merge<int>(even.data(), even.size(), odd.data(), odd.size(), arr.data());
}

int main()
{
	std::vector<int> arr = { 2, 5, 8, 3, 12, 14, 20, -1 };
	sortSpecialArray(arr);

	for (size_t i = 0; i < arr.size(); i++)
		std::cout << arr[i] << ' ';
}