#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

class Graph
{
private:
	std::vector<std::list<size_t>> adj;
	size_t verticesCount;

	bool oriented;

public:
	Graph(size_t verticesCount, bool oriented);
	void addEdge(size_t start, size_t end);
	Graph getTransposedGraph() const;

private:
	bool DFS_containsCycle(std::vector<bool>& visited, std::vector<bool>& stack, size_t currentVertex) const;
	bool BFS_isBipartite(std::vector<size_t>& visited, size_t start) const;
	void DFSrec_topologicalSorting(std::vector<bool>& visited, std::stack<size_t>& currentRes, size_t currentVertex) const;

	void DFS_rec_SCC(const Graph& g, std::vector<bool>& visited, std::vector<bool>& lastlyVisited, size_t currentVertex) const;
	void DFSrec_SCC(const Graph& g, std::vector<size_t> topoSort) const;

public:
	void BFS(size_t start, size_t end, std::vector<size_t>& shortestPath) const;
	bool isCyclic() const;
	bool isBipartite() const;
	void topologicalSorting(std::vector<size_t>& topoSort) const;
	void SCC() const;
};

void Graph::BFS(size_t start, size_t end, std::vector<size_t>& shortestPath) const
{
	if (start >= verticesCount || end >= verticesCount)
		throw "Invalid vertices";

	std::queue<size_t> q;
	std::vector<size_t> prev(verticesCount);
	std::vector<bool> visited(verticesCount, false);

	q.push(start);
	visited[start] = true;

	while (!q.empty())
	{
		size_t current = q.front();
		q.pop();

		if (current == end)
		{
			while (current != start)
			{
				shortestPath.push_back(current);
				current = prev[current];
			}
			shortestPath.push_back(start);

			std::reverse(shortestPath.begin(), shortestPath.end());
			return;
		}

		for (auto it = adj[current].begin(); it != adj[current].end(); ++it)
		{
			if (visited[*it])
				continue;

			q.push(*it);
			prev[*it] = current;
			visited[*it] = true;
		}
	}
}

bool Graph::DFS_containsCycle(std::vector<bool>& visited, std::vector<bool>& stack, size_t currentVertex) const
{
	visited[currentVertex] = true;
	stack[currentVertex] = true;

	for (auto it = adj[currentVertex].begin(); it != adj[currentVertex].end(); ++it)
		if (stack[*it] || DFS_containsCycle(visited, stack, *it))
			return true;

	stack[currentVertex] = false;
	return false;
}
bool Graph::isCyclic() const
{
	if (!oriented)
		throw "The graph should be oriented!";

	std::vector<bool> visited(verticesCount, false);
	std::vector<bool> stack(verticesCount, false);

	for (size_t i = 0; i < visited.size(); i++)
		if (!visited[i] && DFS_containsCycle(visited, stack, i))
			return true;

	return false;
}

bool Graph::BFS_isBipartite(std::vector<size_t>& visited, size_t start) const
{
	std::queue<size_t> q;
	q.push(start);
	visited[start] = true;

	while (!q.empty())
	{
		size_t current = q.front();
		q.pop();

		size_t currentColour = visited[current];

		for (auto it = adj[current].begin(); it != adj[current].end(); it++)
		{
			if (visited[*it] == currentColour)
				return false;

			if (visited[*it])
				continue;

			q.push(*it);
			visited[*it] = currentColour == 1 ? 2 : 1;
		}
	}

	return true;
}
bool Graph::isBipartite() const
{
	if (oriented)
		throw "The graph should NOT be oriented!";

	std::vector<size_t> visited(verticesCount, 0);

	for (size_t i = 0; i < visited.size(); i++)
		if (!visited[i] && !BFS_isBipartite(visited, i))
			return false;

	return true;
}

void Graph::DFSrec_topologicalSorting(std::vector<bool>& visited, std::stack<size_t>& currentRes, size_t currentVertex) const
{
	visited[currentVertex] = true;

	for (auto it = adj[currentVertex].begin(); it != adj[currentVertex].end(); ++it)
	{
		if (visited[*it])
			continue;

		DFSrec_topologicalSorting(visited, currentRes, *it);
	}

	currentRes.push(currentVertex);
}
void Graph::topologicalSorting(std::vector<size_t>& topoSort) const
{
	// Can be made to detect a cycle during the topological sorting and thus to avoid traversing the graph twice.
	// !! This check shouldn't be done when topologicalSorting is used in SCC. !!
	//if (isCyclic())
	//	throw "Only acyclic graphs can be sorted topologically!";

	std::vector<bool> visited(verticesCount, false);
	std::stack<size_t> result;

	for (size_t i = 0; i < visited.size(); i++)
	{
		if (visited[i])
			continue;

		DFSrec_topologicalSorting(visited, result, i);
	}

	while (!result.empty())
	{
		topoSort.push_back(result.top());
		result.pop();
	}
}

void Graph::DFS_rec_SCC(const Graph& g, std::vector<bool>& visited, std::vector<bool>& lastlyVisited, size_t currentVertex) const
{
	visited[currentVertex] = true;
	lastlyVisited[currentVertex] = true;

	for (auto it = g.adj[currentVertex].begin(); it != g.adj[currentVertex].end(); ++it)
	{
		if (visited[*it])
			continue;

		DFS_rec_SCC(g, visited, lastlyVisited, *it);
	}
}
void Graph::DFSrec_SCC(const Graph& g, std::vector<size_t> topoSort) const
{
	std::vector<bool> visited(verticesCount, false);

	std::cout << "The strongly connected components are:" << std::endl;

	for (size_t i = 0; i < topoSort.size(); i++)
	{
		if (visited[topoSort[i]])
			continue;

		std::vector<bool> lastlyVisited(verticesCount, false);

		DFS_rec_SCC(g, visited, lastlyVisited, topoSort[i]);

		for (size_t j = 0; j < lastlyVisited.size(); j++)
		{
			if (lastlyVisited[j])
				std::cout << j << ' ';
		}
		std::cout << std::endl;

		lastlyVisited.clear();
	}
}
void Graph::SCC() const
{
	std::vector<size_t> topoSort;
	topologicalSorting(topoSort);

	Graph transposed = getTransposedGraph();

	DFSrec_SCC(transposed, topoSort);
}


Graph::Graph(size_t verticesCount, bool oriented) : adj(verticesCount), verticesCount(verticesCount), oriented(oriented)
{}
void Graph::addEdge(size_t start, size_t end)
{
	adj[start].push_back(end);
	if (!oriented)
		adj[end].push_back(start);
}
Graph Graph::getTransposedGraph() const
{
	Graph transposedGraph(verticesCount, true);

	for (size_t i = 0; i < adj.size(); i++)
	{
		for (auto j = adj[i].begin(); j != adj[i].end(); ++j)
			transposedGraph.addEdge(*j, i);
	}
	return transposedGraph;
}


int main()
{
	
}