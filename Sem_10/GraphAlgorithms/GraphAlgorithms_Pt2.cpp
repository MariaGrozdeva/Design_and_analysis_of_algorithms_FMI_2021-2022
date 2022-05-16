#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <tuple>
#include "UnionFind.h"

using Edge = std::tuple<size_t, size_t, int>;
void printEdge(const Edge& e)
{
	size_t start = std::get<0>(e);
	size_t end = std::get<1>(e);
	int weight = std::get<2>(e);

	std::cout << start << ' ' << end << ' ' << weight << std::endl;
}

class Graph
{
private:
	std::vector<std::list<std::pair<size_t, int>>> adj;
	size_t verticesCount;

	bool oriented;

public:
	Graph(size_t verticesCount, bool oriented);
	void addEdge(size_t start, size_t end, int weight);

	void Dijkstra(size_t start, std::vector<size_t>& distances) const; // O((n+m)*lgn)
	void BellmanFord(size_t start, std::vector<int>& distances) const; // O(n*(n+m))
	void FloydWarshall(std::vector<std::vector<int>>& distances) const; // O(n^3)

	int Prim(std::vector<Edge>& mst) const; // O((n+m)*lgn)
	int Kruskal(std::vector<Edge>& mst) const; // O(mlgm)
};

void Graph::Dijkstra(size_t start, std::vector<size_t>& distances) const
{
	distances.resize(verticesCount, SIZE_MAX);

	struct VertexDistancePair
	{
		size_t vertex;
		size_t distFromStart;

		bool operator<(const VertexDistancePair& other) const
		{
			return distFromStart > other.distFromStart;
		}
	};

	std::priority_queue<VertexDistancePair> q;

	distances[start] = 0;
	q.push({ start, 0 });

	while (!q.empty())
	{
		VertexDistancePair current = q.top();
		q.pop();

		size_t currentVertex = current.vertex;
		size_t currentDist = current.distFromStart;

		for (auto it = adj[currentVertex].begin(); it != adj[currentVertex].end(); ++it)
		{
			size_t currentSuccessor = (*it).first;
			size_t currentWeight = (*it).second;

			if (distances[currentVertex] + currentWeight < distances[currentSuccessor])
			{
				distances[currentSuccessor] = distances[currentVertex] + currentWeight;
				q.push({ currentSuccessor, distances[currentSuccessor] });
			}
		}
	}
}
void Graph::BellmanFord(size_t start, std::vector<int>& distances) const
{
	distances.resize(verticesCount, INT_MAX);
	distances[start] = 0;

	bool hasChanged = true;
	for (size_t t = 0; t < verticesCount - 1; t++)
	{
		if (!hasChanged)
			break;
		hasChanged = false;

		for (size_t i = 0; i < verticesCount; i++)
		{
			if (distances[i] == INT_MAX)
				continue;

			for (auto it = adj[i].begin(); it != adj[i].end(); ++it)
			{
				if (distances[i] + (*it).second < distances[(*it).first])
				{
					distances[(*it).first] = distances[i] + (*it).second;
					hasChanged = true;
				}
			}
		}
	}

	for (size_t i = 0; i < verticesCount; i++) // check for a negative cycle
	{
		for (auto it = adj[i].begin(); it != adj[i].end(); ++it)
		{
			if ((distances[i] != INT_MAX) && ((distances[i] + (*it).second) < distances[(*it).first]))
				throw "Negative cycle detected!";
		}
	}
}
void Graph::FloydWarshall(std::vector<std::vector<int>>& distances) const
{
	distances.resize(verticesCount, std::vector<int>(verticesCount, INT_MAX));

	// mark all edges
	for (size_t i = 0; i < verticesCount; i++)
	{
		for (auto it = adj[i].begin(); it != adj[i].end(); ++it)
			distances[i][(*it).first] = (*it).second;
	}

	// min distance from i to i is 0 for every vertex
	for (size_t i = 0; i < verticesCount; i++)
		distances[i][i] = 0;

	for (size_t k = 0; k < verticesCount; k++) // intermediate vertices
	{
		for (size_t i = 0; i < verticesCount; i++) // start vertex
		{
			for (size_t j = 0; j < verticesCount; j++) // end vertex
			{
				if ((distances[i][k] != INT_MAX && distances[k][j] != INT_MAX) && (distances[i][j] > distances[i][k] + distances[k][j]))
						distances[i][j] = distances[i][k] + distances[k][j];
			}
		}
	}
}

int Graph::Prim(std::vector<Edge>& mst) const
{
	if (oriented)
		throw "The graph should NOT be oriented!";

	int mstWeight = 0;
	size_t addedEdges = 0;

	std::vector<bool> visited(verticesCount, false);

	auto comp = [](const Edge& lhs, const Edge& rhs) { return std::get<2>(lhs) > std::get<2>(rhs); };
	std::priority_queue<std::tuple<size_t, size_t, int>, std::vector<std::tuple<size_t, size_t, int>>, decltype(comp)> q(comp);

	q.push(std::make_tuple(0, 0, 0)); // virtual edge for the start

	while (addedEdges < verticesCount - 1)
	{
		auto currentEdge = q.top();
		q.pop();

		size_t currentEdgeStart = std::get<0>(currentEdge);
		size_t currentEdgeEnd = std::get<1>(currentEdge);
		int currentEdgeWeight = std::get<2>(currentEdge);

		if (visited[currentEdgeEnd])
			continue;

		mstWeight += currentEdgeWeight;

		if (currentEdgeStart != currentEdgeEnd) // in order not to count the virtual edge
		{
			addedEdges++;
			std::cout << "Added edge: " << currentEdgeStart << "----" << currentEdgeEnd << " with weight: " << currentEdgeWeight << std::endl;
			mst.emplace_back(currentEdgeStart, currentEdgeEnd, currentEdgeWeight);
		}
		visited[currentEdgeEnd] = true;

		for (auto it = adj[currentEdgeEnd].begin(); it != adj[currentEdgeEnd].end(); ++it)
			q.push(std::make_tuple(currentEdgeEnd, (*it).first, (*it).second));
	}

	return mstWeight;
}
int Graph::Kruskal(std::vector<Edge>& mst) const
{
	if (oriented)
		throw "The graph should NOT be oriented!";

	size_t mstWeight = 0;
	size_t addedEdges = 0;

	std::vector<Edge> edges;
	for (size_t i = 0; i < adj.size(); i++)
		for (auto it = adj[i].begin(); it != adj[i].end(); ++it)
			edges.emplace_back(i, (*it).first, (*it).second);

	std::sort(edges.begin(), edges.end(), [](const Edge& lhs, const Edge& rhs)
		{
			return std::get<2>(lhs) < std::get<2>(rhs);
		});

	UnionFind uf(verticesCount);

	for (size_t i = 0; addedEdges < verticesCount - 1; i++)
	{
		auto currentEdge = edges[i];

		size_t currentEdgeStart = std::get<0>(currentEdge);
		size_t currentEdgeEnd = std::get<1>(currentEdge);
		int currentEdgeWeight = std::get<2>(currentEdge);

		if (!uf.Union(currentEdgeStart, currentEdgeEnd)) // If edge "start---end" is added, it will form a cycle
			continue;

		std::cout << "Added edge: " << currentEdgeStart << "----" << currentEdgeEnd << " with weight: " << currentEdgeWeight << std::endl;

		mst.emplace_back(currentEdgeStart, currentEdgeEnd, currentEdgeWeight);
		mstWeight += currentEdgeWeight;
		addedEdges++;
	}

	return mstWeight;
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
	
}
