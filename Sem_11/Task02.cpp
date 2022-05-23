#include <iostream>
#include <cassert>
#include <vector>
#include <string>

int getNextOpeningBracketIndex(const char* str)
{
	for (size_t i = 0; *str != '\0'; i++, str++)
		if (*str == '[')
			return i;

	return -1;
}

size_t minimumSwapsNeededForBalancing(std::string& str)
{
	size_t nextPosOfOpeningBracket = 0;
	size_t result = 0;
	int count = 0;

	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == '[')
		{
			++nextPosOfOpeningBracket;
			++count;
		}
		else
		{
			--count;
		}

		if (count < 0)
		{
			int nextOpeningBracketIndFromI = getNextOpeningBracketIndex(str.c_str() + i);
		    assert(nextOpeningBracketIndFromI > 0);
		    
			result += nextOpeningBracketIndFromI;		    
			std::swap(str[i], str[i + nextOpeningBracketIndFromI]);

			i++;
			count = 0;
		}
	}
	return result;
}

int main()
{
	std::string str("[]][][");
	std::cout << "Swaps: " << minimumSwapsNeededForBalancing(str) << std::endl;
	std::cout << str << std::endl;
}