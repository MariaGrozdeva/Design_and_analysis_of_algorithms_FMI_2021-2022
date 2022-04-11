#include <iostream>
#include <vector>
#include <cstdlib>

size_t getFirstMissing(std::vector<int>& v) // this function CHANGES the input array
{
	for (size_t i = 0; i < v.size(); i++)
		if (abs(v[i]) <= v.size())
			v[abs(v[i]) - 1] = -abs(v[abs(v[i]) - 1]);

	for (size_t i = 0; i < v.size(); i++)
		if (v[i] > 0)
			return i + 1;

	return v.size() + 1;
}

int main()
{
	std::vector<int> nums = { 7, 7, 5, 4, 6, 2, 8, 100000 };
	std::cout << "The first missing number is: " << getFirstMissing(nums) << std::endl;

	for (size_t i = 0; i < nums.size(); i++) // the index of the only positive number (counting from 1) is exactly the first missing one
		std::cout << nums[i] << ' ';
}