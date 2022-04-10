#include <iostream>
#include <vector>

template <class T>
size_t mergeModified(T* arr1, size_t len1, T* arr2, size_t len2)
{
	T* result = new T[len1 + len2];

	size_t cursor1 = 0;
	size_t cursor2 = 0;
	size_t resultCursor = 0;

	size_t inversionCount = 0;

	while (cursor1 < len1 && cursor2 < len2)
	{
		if (arr1[cursor1] < arr2[cursor2])
			result[resultCursor++] = arr1[cursor1++];
		else
		{
			inversionCount += (len1 - cursor1);
			result[resultCursor++] = arr2[cursor2++];
		}
	}

	while (cursor1 < len1)
		result[resultCursor++] = arr1[cursor1++];
	while (cursor2 < len2)
		result[resultCursor++] = arr2[cursor2++];

	for (size_t i = 0; i < len1 + len2; i++)
		arr1[i] = result[i];

	delete[] result;
	return inversionCount;
}

template <class T>
size_t inversionCount(T* arr, size_t len) // O(nlgn)
{
	if (len == 1)
		return 0;

	size_t mid = len / 2;

	size_t x = inversionCount(arr, mid);
	size_t y = inversionCount(arr + mid, len - mid);

	size_t z = mergeModified<T>(arr, mid, arr + mid, len - mid);

	return x + y + z;
}

int main()
{
	int arr[] = { 10, 9, 8, 7, 6, 5 }; // number of inversions: (n-1)*n / 2 = 5*6 / 2 = 15
	std::cout << inversionCount(arr, sizeof(arr) / sizeof(int));
}