#pragma once

template <typename T>
class KDTree
{
	class Node;

public:
	// Constructor initializes root node and dimensions of the kd tree
	KDTree(int d) : root(nullptr), width(0), height(0), depth(d)	{ }

	// Constructor initializes root node and dimensions with region in the kd tree
	KDTree(int w, int h, int d) : root(nullptr), width(w), height(h), depth(d) { }

	// Destructor
	~KDTree()
	{
		clear(root);

		root = nullptr;
	}

	// Insert a point into kd tree
	// Calls utility method to facilitate insertion
	void insert(const T& v, std::vector<int> p)
	{
		root = insert(root, v, p, 0);
	}

	void insert(const T& v, glm::vec2 p)
	{
		std::vector<int> convertedVector = { static_cast<int>(p.x), static_cast<int>(p.y) };
		root = insert(root, v, convertedVector, 0);
	}

	void insert(const T& v, glm::vec3 p)
	{
		std::vector<int> convertedVector = { static_cast<int>(p.x), static_cast<int>(p.y), static_cast<int>(p.z) };
		root = insert(root, v, convertedVector, 0);
	}

	// Remove a point from kd tree
	// Calls utility method to facilitate removal
	void remove(std::vector<int> p)
	{
		root = remove(root, p, 0);
	}

	// Searches for the minimum point within a specified dimension
	// Calls utility method to facilitate search
	T getMin(int d)
	{
		if (d < depth)
			return (getMin(root, d, 0))->value;
	}

	// Searches for the nearest neighbors within a region
	// Calls utility method to facilitate search
	// Stores points within region in nearestPoints
	std::vector<T> nearestNeighbor(std::vector<int>& low, std::vector<int>& high)
	{
		std::vector<T> nearestPoints;

		nearestNeighbor(low, high, nearestPoints, root, 0);

		return nearestPoints;
	}

	std::vector<T> nearestNeighbor(std::vector<int>& queryPoint, float radius, bool isToroidal)
	{
		std::vector<T> nearestPoints;

		nearestNeighbor(queryPoint, radius, nearestPoints, root, 0, isToroidal);

		return nearestPoints;
	}

	// Traverses kd tree by level order
	// Calls utility method to facilitate traversal
	// Calls visitor function to complete traversal
	std::vector<T> traverseLevelOrder()
	{
		std::vector<T> orderedValues;

		visitLevelOrder(root, orderedValues);

		return orderedValues;
	}

private:
	class Node
	{
		friend class KDTree<T>;

	public:
		Node(const T& v, std::vector<int> p) 
			: value(v), point(p), left(nullptr), right(nullptr)
		{ }

	private:
		KDTree<T>::Node* left;
		KDTree<T>::Node* right;

		std::vector<int> point;
		T value;
	};

	void clear(KDTree<T>::Node* node)
	{
		KDTree::Node* tmp = node;

		//If empty tree return NULL
		if (node == nullptr)
			return;

		//Go to the left subtree
		clear(node->left);

		//Go to the right subtree
		clear(node->right);

		//Delete node
		delete tmp;
	}

	KDTree<T>::Node* insert(KDTree<T>::Node* root, const T& v, std::vector<int> p, int d)
	{
		// Check if tree is empty or leaf node
		if (root == nullptr)
			return new KDTree<T>::Node(v, p);

		// Determine which dimension to use for comparison
		int cd = d % depth;

		// Compare the new point with root on current dimension 
		// Determines which side of the branch visit
		if (p[cd] < (root->point[cd]))
			root->left = insert(root->left, v, p, d + 1);
		else
			root->right = insert(root->right, v, p, d + 1);

		return root;
	}

	// Determine minimum between three points
	KDTree<T>::Node* minNode(KDTree<T>::Node* a, KDTree::Node* b, KDTree::Node* c, int d)
	{
		KDTree<T>::Node* res = a;

		if (b != nullptr && b->point[d] < res->point[d])
			res = b;

		if (c != nullptr && c->point[d] < res->point[d])
			res = c;

		return res;
	}

	KDTree<T>::Node* getMin(KDTree<T>::Node* root, int d, int k)
	{
		// Base case
		if (root == nullptr)
			return nullptr;

		// Current dimension is calculated using current depth and kd tree dimension
		int cd = k % depth;

		// Compare point with root with respect to current dimension
		if (cd == d)
		{
			// Root is a leaf node
			if (root->left == nullptr)
				return root;

			// Recurse to the left subtree and find left most leaf node
			return getMin(root->left, d, k + 1);
		}

		// If current dimension is different then minimum point is either the root, a minumum node in the left subtree or a minimum node in the right subtree
		return minNode(root, getMin(root->left, d, k + 1), getMin(root->right, d, k + 1), d);
	}

	KDTree<T>::Node* remove(KDTree<T>::Node* root, std::vector<int> point, int d)
	{
		// Check if tree is empty
		if (root == nullptr)
			return nullptr;

		// Current dimension 
		int cd = d % depth;

		// Delete the root of a subtree
		if (root->point.size() == point.size() && equal(root->point.begin(), root->point.end(), point.begin()))
		{
			// If root node has a right subtree
			if (root->right != nullptr)
			{
				// Find minimum of current node dimension in right subtree
				KDTree<T>::Node* min = getMin(root->right, cd, 0);

				// Replace root with minimum node
				for (int i = 0; i < depth; i++)
					root->point[i] = min->point[i];

				// Recursively delete minimum node
				root->right = remove(root->right, min->point, d + 1);
			}
			else if (root->left != nullptr)
			{
				// Find minimum of current node dimension in left subtree
				KDTree<T>::Node* min = getMin(root->left, cd, 0);

				// Replace root with minimum node
				for (int i = 0; i < depth; i++)
					root->point[i] = min->point[i];

				// Recursively delete minimum node
				root->right = remove(root->left, min->point, d + 1);
			}
			// Node deleted is a leaf node
			else
			{
				delete root;

				return nullptr;
			}

			return root;
		}

		// If current node does not contain point to be deleted
		// And if node to be deleted is less than current node on current dimension
		// Recurse to the left subtree
		if (point[cd] < root->point[cd])
			root->left = remove(root->left, point, d + 1);
		// Recurse to the right subtree
		else
			root->right = remove(root->right, point, d + 1);

		return root;
	}

	void nearestNeighbor(const std::vector<int>& low, const std::vector<int>& high, std::vector<T>& nearestPoints, KDTree<T>::Node* node, int d)
	{
		if (node != nullptr)
		{
			int i;

			// Check if node is within range
			for (i = 0; i < depth; i++)
			{
				// If point is outside range exit loop
				if (low[i] > node->point[i] || high[i] < node->point[i])
					break;
			}

			// If loop completed iterating point is within bounding range
			if (i == depth)
				nearestPoints.push_back(node->value);

			// Move to next dimension 
			++d;
			d = d % depth;

			// If point at current dimension is greater than low point at current dimension, recurse to the left subtree
			if (low[d] <= node->point[d])
				nearestNeighbor(low, high, nearestPoints, node->left, d);

			// If point at current dimension is less than high point at current dimension, recurse to the right subtree
			if (high[d] >= node->point[d])
				nearestNeighbor(low, high, nearestPoints, node->right, d);
		}
	}

	void nearestNeighbor(const std::vector<int>& queryPoint, float radius, std::vector<T>& nearestPoints, KDTree<T>::Node* node, int d, bool isToroidal)
	{
		double w = 0.0;

		if (isToroidal)
			w = vectorToroidalDistance(queryPoint, node->point, width, height);
		else
			w = vectorDistance(queryPoint, node->point);

		if (node->left == nullptr && node->right == nullptr)
		{
			if (w < radius * radius)
				nearestPoints.push_back(node->value);

			return;
		}

		if (w < radius * radius)
			nearestPoints.push_back(node->value);

		++d;
		d = d % depth;

		double q = queryPoint[d];
		double n = node->point[d];

		if (q < n)
		{
			if (q - radius <= n && node->left != nullptr)
				nearestNeighbor(queryPoint, radius, nearestPoints, node->left, d, isToroidal);

			if (q + radius > n && node->right != nullptr)
			{
				nearestNeighbor(queryPoint, radius, nearestPoints, node->right, d, isToroidal);
				return;
			}
		}
		else
		{
			if (q + radius > n && node->right != nullptr)
				nearestNeighbor(queryPoint, radius, nearestPoints, node->right, d, isToroidal);

			if (q - radius <= n && node->left != nullptr)
			{
				nearestNeighbor(queryPoint, radius, nearestPoints, node->left, d, isToroidal);
				return;
			}
		}
	}

	void visitLevelOrder(KDTree<T>::Node* node, std::vector<T>& orderedValues)
	{
		//Declare queue of nodes used to accumulate sibling nodes
		std::queue<KDTree<T>::Node*> siblingNodes;

		//Declare a node pointer and set it to the current node
		KDTree<T>::Node* currentNode = node;

		//Loop until current node reaches NULL
		while (currentNode != nullptr)
		{
			//Push value into result vector
			orderedValues.push_back(currentNode->value);

			//If the left branch is not NULL, enqueue left branch
			if (currentNode->left != nullptr)
				siblingNodes.push(currentNode->left);

			//If the right branch is not NULL, enqueue right branch
			if (currentNode->right != nullptr)
				siblingNodes.push(currentNode->right);

			//If queue is not empty set current node to the front of the queue and pop from the queue
			if (!siblingNodes.empty())
			{
				currentNode = siblingNodes.front();
				siblingNodes.pop();
			}
			//Else set the current node to NULL
			else
				currentNode = nullptr;
		}
	}

	float vectorDistance(const std::vector<int>& lhs, const std::vector<int>& rhs)
	{
		float dx = lhs[0] - rhs[0];
		float dy = lhs[1] - rhs[1];

		return sqrt(dx * dx + dy * dy);
	}

	float vectorToroidalDistance(const std::vector<int>& lhs, const std::vector<int>& rhs, float w, float h)
	{
		float dx = lhs[0] - rhs[0];
		float dy = lhs[1] - rhs[1];

		if (dx > w / 2)
			dx = w - dx;

		if (dy > h / 2)
			dy = h - dy;

		return sqrt(dx * dx + dy * dy);
	}

	// Root node
	KDTree<T>::Node* root;

	// Tree dimensions
	int depth;

	// Region dimesions
	int width;
	int height;
};