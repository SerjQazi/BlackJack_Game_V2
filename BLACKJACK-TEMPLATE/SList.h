#pragma once

// forward declaration of list
// enforces order of compilation
template <typename T>
class SList;

// forward declaration of operator << 
// enforces order of compilation
template <typename T>
std::ostream& operator<<(std::ostream& out, const SList<T>& list);

/*
	Template class representing a Single Linked List of Nodes
*/
template <typename T>
class SList
{
	// overriding operator << to print list values
	friend std::ostream& operator<< <T>(std::ostream& out, const SList<T>& list);

public:
	class Node;
	class Iterator;

	// default constructor
	SList() : head(nullptr), tail(nullptr), sz(0)
	{ }

	// destructor
	~SList()
	{
		clear();
	}

	// remove all nodes
	void clear()
	{
		// remove a node until empty
		while (!empty())
			pop_front();
	}

	// check for empty list
	bool empty() const
	{
		return sz == 0;
	}

	// return number of members
	size_t size() const
	{
		return sz;
	}

	// return reference to first value in list
	// precondition: list is not empty
	T& front()
	{
		return head->value;
	}

	// return reference to last value in list
	// precondition: list is not empty
	T& back()
	{
		return tail->value;
	}

	// insert a value at the beginning of the list
	void push_front(const T& value)
	{
		// create new node with value
		SList<T>::Node* new_node = new SList<T>::Node(value);

		if (empty())
		{
			// if the list is empty, new node becomes both head and tail
			head = tail = new_node;
		}
		else
		{
			// if the list is not empty, insert new node before head
			new_node->next = head;
			head = new_node;
		}

		++sz;
	}

	// insert a value at the end of the list
	void push_back(const T& value)
	{
		// create new node with value
		SList<T>::Node* new_node = new SList<T>::Node(value);

		if (empty())
		{
			// if the list is empty, new node becomes both head and tail
			head = tail = new_node;
		}
		else
		{
			// if the list is not empty, insert new node after tail
			tail->next = new_node;
			tail = new_node;
		}

		++sz;
	}

	// remove first element from the list
	// precondition: list is not empty
	void pop_front()
	{
		// save pointer to old head
		SList<T>::Node* old_head = head;

		if (head == tail)
			// if list contained only one element, list is now empty
			head = tail = nullptr;
		else
			// otherwise, reposition head pointer to next element in list
			head = head->next;

		// blow away the old head node
		delete old_head;

		--sz;
	}

	// remove last element from the list
	// precondition: list is not empty
	void pop_back()
	{
		// save old list tail
		SList<T>::Node* old_tail = tail;

		if (head == tail)
			// if list contained only one element, list is now empty
			head = tail = nullptr;
		else
		{
			// find new tail by starting at head
			tail = head;

			while (tail->next != old_tail)
				tail = tail->next;

			// the new tail is the node before old tail
			tail->next = nullptr;
		}

		// blow away old tail node
		delete old_tail;

		--sz;
	}

	// return iterator set to first element in list
	SList<T>::Iterator& begin()
	{
		SList<T>::Iterator it(head);
		return it;
	}

	// return iterator past last element in list
	SList<T>::Iterator end()
	{
		SList<T>::Iterator it(nullptr);
		return it;
	}

	// erase the list element at pos
	// precondition: pos is a valid iterator
	// returns: an iterator at the element immediately after pos
	SList<T>::Iterator erase(SList<T>::Iterator pos)
	{
		SList<T>::Node* target = pos.node;  // save target to be erased

		++pos;  // advance iterator

		if (target == head)
			pop_front();
		else if (target == tail)
			pop_back();
		else
		{
			// find the node before target
			Node* tmp = head;

			while (tmp->next != target)
				tmp = tmp->next;
			// unlink target node
			tmp->next = target->next;
			// delete target node
			delete target;
			--sz;
		}

		return pos; // return advanced iterator
	}

	// insert a value before pos
	// precondition: pos is a valid iterator or end()
	// returns: an iterator at the inserted value
	SList<T>::Iterator insert(SList<T>::Iterator pos, const T& value)
	{
		if (pos == begin())
		{
			// insert new node before head
			push_front(value);

			return head;
		}
		else if (pos == end())
		{
			push_back(value);

			return tail;
		}
		else
		{
			// find the node before pos
			typename SList<T>::Node* tmp = head;

			while (tmp->next != pos.node)
				tmp = tmp->next;

			// create new node to be inserted
			typename SList<T>::Node* new_node = new SList<T>::Node(value);

			// insert new_node between tmp and pos
			tmp->next = new_node;
			new_node->next = pos.node;

			++sz;

			return new_node;
		}
	}

	// find a value in the list
	// returns: a valid iterator if found, end() if not found
	SList<T>::Iterator find(const T& value)
	{
		for (typename SList<T>::Node* node = head; node; node = node->next)
			if (node->value == value)
				return node;

		return end();
	}

private:
	// pointers to first and last nodes in the list
	SList<T>::Node* head;
	SList<T>::Node* tail;

	size_t sz;
};

// Iterator class -- represents a position in the list.
	// Used to gain access to individual elements, as well as
	// insert, find, and erase elements
template <typename T>
class SList<T>::Iterator
{
	// SList class needs access to private members of Iterator
	friend class SList<T>;

public:
	// default constructor: iterator not valid until initialized
	Iterator() : node(nullptr)
	{ }

	// parameterized constructor
	Iterator(SList<T>::Node* n) : node(n)
	{ }

	// equality operator (==)
	// checks whether both iterators represent the same position
	bool operator== (const SList<T>::Iterator& rhs) const
	{
		return node == rhs.node;
	}

	// inequality operator (!=)
	// checks whether iterators represent different positions
	bool operator!= (const SList<T>::Iterator& rhs) const
	{
		return node != rhs.node;
	}

	// dereference operator (unary *)
	// returns a reference to the data value at the iterator position
	// precondition: iterator is valid
	T& operator*() const
	{
		return node->value;
	}

	// preincrement operator
	// advances to next node and returns itself
	Iterator& operator++()
	{
		node = node->next;

		return *this;
	}

	// postincrement operator
	// advances to next node and returns old copy of itself
	Iterator operator++(int)
	{
		SList<T>::Iterator tmp = *this;

		node = node->next;

		return tmp;
	}

private:
	// the iterator holds a pointer to the "current" list node
	SList<T>::Node* node;
};

/*
	Class representing a single linked list node
*/
template <typename T>
class SList<T>::Node
{
	friend class SList<T>;
	friend class SList<T>::Iterator;

	friend std::ostream& operator<< <T>(std::ostream& out, const SList<T>& list);

public:
	// constructor
	Node(const T& v) : value(v), next(nullptr)
	{ }

	T getValue()
	{
		return value;
	}

	SList<T>::Node* getNext()
	{
		return next;
	}

private:
	// the data value
	T value;

	// pointer to the next node
	Node* next;
};

template <typename T>
std::ostream& operator<< <T>(std::ostream& out, const SList<T>& list)
{
	typename SList<T>::Node* it;

	for (it = list.head; it != nullptr; it = it->next)
		out << it->value << " ";

	return out;
}