#include <iostream>
#include <vector>
#include <list>

class Graph
{
private:
	std::vector<std::list<std::pair<size_t, int>>> adj;
	size_t verticesCount;

	bool oriented;

public:
	Graph(size_t verticesCount, bool oriented);
	void addEdge(size_t start, size_t end, int weight);

private:
	void DFS_rec(size_t start, std::vector<bool>& visited, std::vector<size_t>& result) const;
	size_t areConnected(size_t start, size_t end) const;

	Graph removeEdgesWithBiggerWeight(size_t weight) const;

public:
	bool isPartOfMST(size_t start, size_t end) const;
};

void Graph::DFS_rec(size_t start, std::vector<bool>& visited, std::vector<size_t>& result) const
{
	visited[start] = true;
	result.push_back(start);

	for (auto it = adj[start].begin(); it != adj[start].end(); ++it)
	{
		if (visited[(*it).first])
			continue;

		DFS_rec((*it).first, visited, result);
	}
}
size_t Graph::areConnected(size_t start, size_t end) const
{
	std::vector<bool> visited(verticesCount);
	std::vector<size_t> result;

	DFS_rec(start, visited, result);

	return visited[end];
}

Graph Graph::removeEdgesWithBiggerWeight(size_t weight) const
{
	Graph res(verticesCount, false);

	for (size_t i = 0; i < verticesCount; i++)
	{
		for (auto it = adj[i].begin(); it != adj[i].end(); ++it)
		{
			if ((*it).second < weight)
				res.addEdge(i, (*it).first, (*it).second);
		}
	}
	return res;
}

bool Graph::isPartOfMST(size_t start, size_t end) const
{
	size_t weight = -1;
	for (auto it = adj[start].begin(); it != adj[start].end(); ++it)
		if ((*it).first == end)
			weight = (*it).second;

	if (weight == -1)
		return false; // no edge between start and end

	Graph lighterGraph = removeEdgesWithBiggerWeight(weight);
	return !lighterGraph.areConnected(start, end);
}


Graph::Graph(size_t verticesCount, bool oriented) : adj(verticesCount), verticesCount(verticesCount), oriented(oriented)
{}
void Graph::addEdge(size_t start, size_t end, int weight)
{
	adj[start].push_back(std::make_pair(end, weight));
	if (!oriented)
		adj[end].push_back(std::make_pair(start, weight));
}


int main()
{
	Graph g(9, false);
	g.addEdge(0, 1, 4);
	g.addEdge(0, 7, 8);
	g.addEdge(1, 2, 8);
	g.addEdge(1, 7, 11);
	g.addEdge(2, 3, 7);
	g.addEdge(2, 5, 4);
	g.addEdge(3, 4, 9);
	g.addEdge(3, 5, 14);
	g.addEdge(5, 4, 10);
	g.addEdge(6, 5, 2);
	g.addEdge(7, 6, 1);
	g.addEdge(7, 8, 7);
	g.addEdge(8, 2, 2);
	g.addEdge(8, 6, 6);

	std::cout << g.isPartOfMST(2, 5);
}