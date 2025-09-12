#pragma once

#include "SList.h"

template <typename T>
class Stack
{
public:
	~Stack()
	{
		data.clear();
	}

	void clear()
	{
		data.clear();
	}

	void push(const T& value)
	{
		data.push_front(value);
	}

	void pop()
	{
		data.pop_front();
	}

	T& top()
	{
		return data.front();
	}

	bool empty() const
	{
		return data.empty();
	}

	size_t size() const
	{
		return data.size();
	}

private:
	SList<T> data;
};