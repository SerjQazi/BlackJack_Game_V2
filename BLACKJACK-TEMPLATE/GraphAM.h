#pragma once

#include "GameObject.h"

template <typename Key, typename Value>
class GraphAM
{
public:
	class Vertex;

	GraphAM(int numVerts, bool weighted = false) : maxVertices(numVerts), isWeighted(weighted)
	{
		// Quit if number of vertices is 0 or less
		if (numVerts > 0)
		{
			// Reserve vector size to store vertex labels
			vertices.reserve(maxVertices);

			// Instantiate array to store visited vertices
			vertexVisits = new char[maxVertices];

			// Initialize visited vertices array
			for (int i = 0; i < maxVertices; i++)
				vertexVisits[i] = 0;

			// Instantiate adjacency matrix 
			adjacencyMatrix = new int* [maxVertices];

			// Initialize adjacency matrix to null
			for (int i = 0; i < maxVertices; i++)
			{
				adjacencyMatrix[i] = new int[maxVertices];

				for (int j = 0; j < maxVertices; j++)
					adjacencyMatrix[i][j] = 0;
			}
		}
	}

	~GraphAM()
	{
		if (adjacencyMatrix != nullptr)
		{
			for (int i = 0; i < maxVertices; i++)
			{
				if (adjacencyMatrix[i] != nullptr)
				{
					delete[] adjacencyMatrix[i];

					adjacencyMatrix[i] = nullptr;
				}
			}

			delete[] adjacencyMatrix;

			adjacencyMatrix = nullptr;
		}

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
			for (int j = 0; j < maxVertices; ++j) 
			{
				adjacencyMatrix[i][j] = 0;
			}
		}

		for (int i = 0; i < maxVertices; ++i) 
		{
			vertexVisits[i] = 0;
		}
	}

	GraphAM<Key, Value>::Vertex* push(const Key& n, const Value& v)
	{
		// Check if graph is full
		if ((int)vertices.size() >= maxVertices)
			return nullptr;

		GraphAM<Key, Value>::Vertex* vertex = new GraphAM<Key, Value>::Vertex(n, v);

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

	bool attachEdge(Key startVertexKey, Key endVertexKey, int weight = 0)
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
			adjacencyMatrix[startIndex][endIndex] = weight;
			adjacencyMatrix[endIndex][startIndex] = weight;
		}
		else
		{
			adjacencyMatrix[startIndex][endIndex] = 1;
			adjacencyMatrix[endIndex][startIndex] = 1;
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
			adjacencyMatrix[startIndex][endIndex] = weight;
		else
			adjacencyMatrix[startIndex][endIndex] = 1;

		return true;
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
		adjacencyMatrix[startIndex][endIndex] = 0;
		adjacencyMatrix[endIndex][startIndex] = 0;

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
		adjacencyMatrix[startIndex][endIndex] = 0;

		return true;
	}

	std::vector<typename GraphAM<Key, Value>::Vertex> nearestNeighbor(const Key startVertexKey)
	{
		std::vector<GraphAM<Key, Value>::Vertex> neighbors;

		int startIndex = findIndex(startVertexKey);

		neighbors.reserve(vertices.size());

		for (int i = 0; i < vertices.size(); ++i)
			if (adjacencyMatrix[startIndex][i] != 0)
				neighbors.push_back(vertices[i]);

		return neighbors;
	}

	int getNextUnvisitedVertex(int index)
	{
		for (int i = 0; i < (int)vertices.size(); i++)
			if (adjacencyMatrix[index][i] == 1 && vertexVisits[i] == 0)
				return i;

		return -1;
	}

	int getEdgeWeight(const Key startIndexKey, const Key endIndexKey)
	{
		int startIndex = findIndex(startIndexKey);
		int endIndex = findIndex(endIndexKey);

		return adjacencyMatrix[startIndex][endIndex];
	}

	void setEdgeWeight(const Key startIndexKey, const Key endIndexKey, int weight)
	{
		int startIndex = findIndex(startIndexKey);
		int endIndex = findIndex(endIndexKey);

		adjacencyMatrix[startIndex][endIndex] = weight;
	}

	int getDegree(const Key& key)
	{
		int index = findIndex(key);
		int degree = 0;

		for (int i = 0; i < maxVertices; i++)
		{
			if (adjacencyMatrix[index][i] != 0)
				degree++;

			if (adjacencyMatrix[i][index] != 0)
				degree++;
		}

		return degree;
	}

	bool topologicalSort(std::vector<Key>& result)
	{
		// Flag to track cycles
		bool hasCycles = false;

		// Copy vertices into temp vector of vertices
		std::vector<GraphAM<Key, Value>::Vertex> tempVerts(vertices);

		std::stack<Key> searchStack;

		// Store total number of vertices
		int tempSize = (int)tempVerts.size();

		// Instantiate temporary adjacency matrix
		char** tempAdjMat = new char* [maxVertices];

		// Iterate and copy all vertices from original adjancency matrix
		for (int i = 0; i < maxVertices; i++)
		{
			tempAdjMat[i] = new char[maxVertices];

			for (int j = 0; j < maxVertices; j++)
				tempAdjMat[i][j] = adjacencyMatrix[i][j];
		}

		// If adjacency matrix size greater than 0
		while (tempSize > 0)
		{
			// Find vertices with no successor
			int v = getVertNoSuccessor(tempAdjMat, tempSize);

			// Exit if vertex cycles
			if (v == -1)
			{
				hasCycles = true;
				break;
			}

			// Store vertex in list if no cycles found
			searchStack.push(tempVerts[v].getKey());

			// Since vertex was visited, remove from temp list and adjacency matrix
			if (v != (tempSize - 1))
			{
				tempVerts.erase(tempVerts.begin() + v);

				for (int row = v; row < tempSize - 1; row++)
					for (int col = 0; col < tempSize; col++)
						tempAdjMat[row][col] = tempAdjMat[row + 1][col];

				for (int col = v; col < tempSize - 1; col++)
					for (int row = 0; row < tempSize; row++)
						tempAdjMat[row][col] = tempAdjMat[row][col + 1];
			}

			tempSize--;
		}

		//Copy stack into result vector
		while (!searchStack.empty())
		{
			result.push_back(searchStack.top());
			searchStack.pop();
		}


		// Clean-up temporary variables
		if (tempAdjMat != nullptr)
		{
			for (int i = 0; i < maxVertices; i++)
			{
				if (tempAdjMat[i] != nullptr)
				{
					delete[] tempAdjMat[i];
					tempAdjMat[i] = nullptr;
				}
			}

			delete[] tempAdjMat;
			tempAdjMat = nullptr;
		}

		// Return whether graph has cycles
		return !hasCycles;
	}

	bool MST(std::vector<Key>& result)
	{
		if (isWeighted)
		{
			// Start at first vertex
			int currentVertex = 0;
			// Set total visited nodes to 0
			int totalChecked = 0;
			// Set size to size of the vertex vector
			int size = (int)vertices.size();

			// Create a vector of edges to track those visited
			std::vector<Edge> edgeInfo;

			// Loop while the number of checked vertices is less than the total number of vertices
			while (totalChecked < size - 1)
			{
				// Set current vertex to visited
				vertexVisits[currentVertex] = 1;
				// Add a visited vertices
				totalChecked++;

				// Loop through and add all unchecked adjacent vertices and their weights into a priority queue
				for (int i = 0; i < size; i++)
				{
					// Go to next iteration If counter is equal to current vertex or vertex visited is true or if adjacency matrix does not have an edge at current vertex
					if (i == currentVertex || vertexVisits[i] == 1 || adjacencyMatrix[currentVertex][i] == 0)
						continue;

					GraphAM<Key, Value>::Edge edge;

					edge.startVertex = currentVertex;
					edge.endVertex = i;
					edge.weight = adjacencyMatrix[currentVertex][i];

					// Create a vector iterator to traverse edges
					typename std::vector<GraphAM<Key, Value>::Edge>::iterator it = find(edgeInfo.begin(), edgeInfo.end(), edge);

					// If end of the vector is reached push edge into vector
					if (it == edgeInfo.end())
						edgeInfo.push_back(edge);
					// If weight found within the iterator is greater than the edge weight reassign new weight to iterator edge
					else if (edge.weight <= (*it).weight)
					{
						(*it).startVertex = edge.startVertex;
						(*it).endVertex = edge.endVertex;
						(*it).weight = edge.weight;
					}
				}

				// If vector of edgeinfo is empty print error
				if (edgeInfo.empty())
					return false;

				// Orders edges from greatest to lowest
				std::sort(edgeInfo.rbegin(), edgeInfo.rend());

				int endIndex = (int)edgeInfo.size() - 1;
				int v1 = edgeInfo[endIndex].startVertex;
				currentVertex = edgeInfo[endIndex].endVertex;

				result.push_back(vertices[v1].getKey());
				result.push_back(vertices[currentVertex].getKey());

				// Remove minimum edge 
				edgeInfo.pop_back();
			}

			// Reset vertices visited
			for (int i = 0; i < maxVertices; i++)
				vertexVisits[i] = 0;

			return true;
		}

		return false;
	}

	std::vector<GraphAM<Key, Value>::Vertex> vertices;
	std::vector<int> distances;

	char* vertexVisits;

	int maxVertices;

private:
	class Edge;

	int** adjacencyMatrix;

	bool isWeighted;

	int minimumDistance(std::vector<int>& distance)
	{
		int min = INT_MAX;
		int index;

		for (int i = 0; i < maxVertices; ++i)
		{
			if (!vertexVisits[i] && distance[i] <= min)
			{
				min = distance[i];
				index = i;
			}
		}

		return index;
	}

	// Find the vetices with no successors
	int getVertNoSuccessor(char** adjMat, int size)
	{
		bool edgeFound = false;

		// Traverse all connected vertices and find ones with no edges
		for (int row = 0; row < size; row++)
		{
			edgeFound = false;

			for (int col = 0; col < size; col++)
			{
				// Exit loop if edge found
				if (adjMat[row][col] != 0)
				{
					edgeFound = true;
					break;
				}
			}

			// Return current row index if edge not found
			if (edgeFound == false)
				return row;
		}

		// Return -1 if edge was found
		return -1;
	}
};

template <typename Key, typename Value>
class GraphAM<Key, Value>::Vertex
{
	friend GraphAM<Key, Value>;

public:
	Vertex() = default;
	Vertex(const Key& k, const Value& v) : key(k), value(v)
	{ }

	Key getKey()
	{
		return key;
	}

	Value getValue()
	{
		return this->value;
	}

	void setValue(Value v)
	{
		this->value = v;
	}

private:
	Key key;
	Value value;
};

template <typename Key, typename Value>
class GraphAM<Key, Value>::Edge
{
	friend GraphAM<Key, Value>;

public:
	Edge() : startVertex(0), endVertex(0), weight(0)
	{ }

	bool operator<(const Edge& e2) const
	{
		return (weight < e2.weight);
	}

	bool operator>(const Edge& e2) const
	{
		return (weight > e2.weight);
	}

	bool operator==(const Edge& e2) const
	{
		return (endVertex == e2.endVertex);
	}

	int startVertex;
	int endVertex;
	int weight;
};