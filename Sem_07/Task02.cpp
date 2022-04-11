#include <iostream>
#include <vector>

void print(size_t k, size_t m)
{
	std::cout << "The indices of the numbers whose difference is divisible by 3n are " << k << " and " << m << '.' << std::endl;
}

bool sameRemainders(const std::vector<int>& v)
{
	size_t sizeTimesThree = 3 * v.size(); // 3n
	std::vector<size_t> remainders(sizeTimesThree, -1); // at every index (corresponding to a certain remainder) we will keep the index of the last element which has
	                                                    // that remainder (mod 3n) or -1, if such doesn't exist

	int currentRemainder;
	for (size_t i = 0; i < v.size(); i++)
	{
		currentRemainder = v[i] % (int)sizeTimesThree;
		if (currentRemainder < 0) // we want the remainders in their positive forms (e.g. -3 % 27 = -3 or 24)
			currentRemainder += sizeTimesThree;

		if (remainders[currentRemainder] == -1)
			remainders[currentRemainder] = i;
		else
		{
			print(remainders[currentRemainder], i);
			return true;
		}
	}

	return false;
}

int main()
{
	std::vector<int> nums = { 4, 1, -3, 8, 16, 19, 22, 11, 24 };
	if (!sameRemainders(nums))
		std::cout << "No such elements!" << std::endl;
}