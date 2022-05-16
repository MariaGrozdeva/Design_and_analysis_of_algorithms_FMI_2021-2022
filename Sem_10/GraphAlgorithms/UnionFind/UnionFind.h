#include <iostream>
#include <vector>

class UnionFind
{
private:
	std::vector<size_t> parents;
	std::vector<size_t> sizes;

public:
	UnionFind(size_t n); // set of n elements (0..n-1)

	bool Union(size_t n, size_t k); // O(log(n))
	size_t Find(size_t n); // O(log(n))
};