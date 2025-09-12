#pragma once

#include "SList.h"

template <typename T>
class Queue
{
public:
	void clear()
	{
		data.clear();
	}

	void enqueue(const T& value)
	{
		data.push_back(value);
	}

	void dequeue()
	{
		data.pop_front();
	}

	T& front()
	{
		return data.front();
	}

	T& back()
	{
		return data.back();
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