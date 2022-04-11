#include <iostream>
#include <vector>

size_t getFirstMissing(const std::vector<size_t>& v)
{
	std::vector<bool> occurrences(v.size(), false);

	for (size_t i = 0; i < v.size(); i++)
		if (v[i] <= v.size())
			occurrences[v[i] - 1] = true;

	for (size_t i = 0; i < v.size(); i++)
		if (!occurrences[i])
			return i + 1;

	return v.size() + 1;
}

int main()
{
	std::vector<size_t> nums = { 7, 1, 3, 5, 4, 6, 2, 8, 100000 };
	std::cout << "The first missing number is: " << getFirstMissing(nums) << std::endl;
}