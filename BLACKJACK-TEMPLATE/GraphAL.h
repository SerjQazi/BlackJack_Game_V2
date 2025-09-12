#pragma once

#include "SList.h"
#include "Stack.h"
#include "Queue.h"

template <typename Key, typename Value>
class GraphAL
{
public:
	class Vertex;

	GraphAL(int numVerts, bool weighted = false) : maxVertices(numVerts), isWeighted(weighted)
	{
		// Quit if number of vertices is 0 or less
		if (numVerts > 0)
		{
			// Reserve vector size to store vertex labels
			vertices.reserve(maxVertices);

			adjacencyList = new SList<int>*[maxVertices];

			// Instantiate array to store visited vertices
			vertexVisits = new char[maxVertices];

			// Initialize visited vertices array
			for (int i = 0; i < maxVertices; ++i)
				vertexVisits[i] = 0;

			for (int i = 0; i < maxVertices; ++i)
				adjacencyList[i] = new SList<int>[maxVertices];
		}
	}

	~GraphAL()
	{
		if (vertexVisits != nullptr)
		{
			delete[] vertexVisits;

			vertexVisits = nullptr;
		}

		if (!vertices.empty())
			vertices.clear();
	}

	void clear() 
	{
		for (int i = 0; i < maxVertices; ++i) 
		{
			if (adjacencyList[i] != nullptr) 
			{
				adjacencyList[i]->clear();
			}
		}
	}

	GraphAL<Key, Value>::Vertex* push(const Key& n, const Value& v)
	{
		// Check if graph is full
		if ((int)vertices.size() >= maxVertices)
			return nullptr;

		GraphAL<Key, Value>::Vertex* vertex = new GraphAL<Key, Value>::Vertex(n, v);

		// Insert vertex if graph is not full
		vertices.push_back(*vertex);

		return vertex;
	}

	int findIndex(const Key& key)
	{
		// Search through list of vertices and return the index where the vertex label was found
		for (int i = 0; i < (int)vertices.size(); ++i)
			if (static_cast<Key>(vertices[i].key) == key)
				return i;

		// Return -1 if label not found in adjacency matrix
		return -1;
	}

	bool attachEdge(const Key startVertexKey, const Key endVertexKey, int weight = 0)
	{
		// Find indicies for labels
		int startIndex = findIndex(startVertexKey);
		int endIndex = findIndex(endVertexKey);

		// Quit if a label is not a vertex
		if (startIndex == -1 || endIndex == -1)
			return false;

		// If graph is weighted insert weights into adjacency matrix
		if (isWeighted)
		{
			vertices[startIndex].weight = weight;
			vertices[endIndex].weight = weight;

			adjacencyList[startIndex]->push_back(endIndex);
			adjacencyList[endIndex]->push_back(startIndex);
		}
		else
		{
			adjacencyList[startIndex]->push_back(endIndex);
			adjacencyList[endIndex]->push_back(startIndex);
		}

		return true;
	}

	bool attachDirectedEdge(const Key startVertexKey, const Key endVertexKey, int weight = 0)
	{
		// Find indicies for labels
		int startIndex = findIndex(startVertexKey);
		int endIndex = findIndex(endVertexKey);

		if (startIndex == -1 || endIndex == -1)
			return false;

		// If graph is weighted insert weights into adjacency matrix
		if (isWeighted)
		{
			vertices[endIndex].weight = weight;

			adjacencyList[startIndex]->push_back(endIndex);
		}
		else
		{
			adjacencyList[startIndex]->push_back(endIndex);
		}

		return true;
	}

	std::vector<GraphAL<Key, Value>::Vertex> nearestNeighbor(const Key startVertexKey)
	{
		std::vector<GraphAL<Key, Value>::Vertex> neighbors;

		int startIndex = findIndex(startVertexKey);

		neighbors.reserve(adjacencyList[startIndex]->size());

		SList<int>::Iterator it = adjacencyList[startIndex]->begin();

		while (it != adjacencyList[startIndex]->end())
		{
			neighbors.push_back(vertices[*it]);

			++it;
		}

		return neighbors;
	}

	bool removeEdge(Key startVertexKey, Key endVertexKey)
	{
		// Find indicies for labels
		int startIndex = findIndex(startVertexKey);
		int endIndex = findIndex(endVertexKey);

		// Quit if a label is not a vertex
		if (startIndex == -1 || endIndex == -1)
			return false;

		// If graph is weighted insert weights into adjacency matrix
		auto it = adjacencyList[startIndex]->find(endIndex);
		if (it != adjacencyList[startIndex]->end())
		{
			adjacencyList[startIndex]->erase(it);
		}
		else
			return false;

		it = adjacencyList[endIndex]->find(startIndex);
		if (it != adjacencyList[endIndex]->end())
		{
			adjacencyList[endIndex]->erase(it);
		}
		else
			return false;

		return true;
	}

	bool removeDirectedEdge(const Key startVertexKey, const Key endVertexKey)
	{
		// Find indicies for labels
		int startIndex = findIndex(startVertexKey);
		int endIndex = findIndex(endVertexKey);

		if (startIndex == -1 || endIndex == -1)
			return false;

		// If graph is weighted insert weights into adjacency matrix
		auto it = adjacencyList[startIndex]->find(endIndex);
		if (it != adjacencyList[startIndex]->end())
		{
			adjacencyList[startIndex]->erase(it);
		}

		return true;
	}

	bool topologicalSort(std::vector<Key>& result)
	{
		if (adjacencyList != nullptr)
		{
			Stack<int> s;

			for (int i = 0; i < maxVertices; ++i)
				if (vertexVisits[i] == 0)
					topologicalSortHelper(i, s);

			while (!s.empty())
			{
				result.push_back(vertices[s.top()].key);
				s.pop();
			}

			for (int i = 0; i < maxVertices; i++)
				vertexVisits[i] = 0;

			return true;
		}

		return false;
	}

	int getNextUnvisitedVertex(int index)
	{
		SList<int>* temp = static_cast<SList<int>*>(adjacencyList[index]);
		SList<int>::Iterator it = temp->begin();

		//iterate to position then check vertexvisits at index of iterator
		while (it != temp->end())
		{
			if (vertexVisits[*it] == 0)
				return *it;

			++it;
		}

		return -1;
	}

	int maxVertices;
	std::vector<int> distances;
	std::vector<GraphAL<Key, Value>::Vertex> vertices;
	char* vertexVisits;

private:
	class Edge;
	
	SList<int>** adjacencyList;
	
	bool isWeighted;

	void topologicalSortHelper(int index, Stack<int>& s)
	{
		vertexVisits[index] = 1;

		SList<int>* row = adjacencyList[index];
		typename SList<int>::Iterator it;

		for (it = row->begin(); it != row->end(); ++it)
			if (vertexVisits[*it] != 1)
				topologicalSortHelper(*it, s);

		s.push(index);
	}
};

template <typename Key, typename Value>
class GraphAL<Key, Value>::Vertex
{
	friend GraphAL<Key, Value>;

public:
	Vertex() = default;
	Vertex(const Key& k, const Value& v, int w = 0) : key(k), value(v), weight(w), next(nullptr)
	{ }

	Key getKey()
	{
		return key;
	}

	Value getValue()
	{
		return value;
	}

	int getWeight()
	{
		return weight;
	}

	void setValue(Value& v)
	{
		this->value = v;
	}

	void setWeight(int w)
	{
		this->weight = w;
	}

	Key key;
	Value value;

private:
	int weight;

	Vertex* next;
};

template <typename Key, typename Value>
class GraphAL<Key, Value>::Edge
{
	friend GraphAL<Key, Value>;

public:
	Edge() : startVertex(0), endVertex(0), weight(0)
	{ }

	bool operator<(const GraphAL<Key, Value>::Edge& e2) const
	{
		return (weight < e2.weight);
	}

	bool operator>(const GraphAL<Key, Value>::Edge& e2) const
	{
		return (weight > e2.weight);
	}

	bool operator==(const GraphAL<Key, Value>::Edge& e2) const
	{
		return (endVertex == e2.endVertex);
	}

	int startVertex;
	int endVertex;
	int weight;
};