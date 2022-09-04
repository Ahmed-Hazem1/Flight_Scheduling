#include<iostream>
using namespace std;

template <typename T>
class node {
public:

	T v; // data
	node<T>* next; // pointer to next node

	node(T x)
	{
		v = x;
		next = NULL;
	}

};

template <class T>
class QueueT {

	// the '<T>' after node indicate that the
	// datatype of template of node should be T
	node<T>* start;
	node<T>* end;

public:

	QueueT()
	{
		start = end = NULL;
	}

	T peek() {
		return front;
	}
	bool Full()
	{
		return((start != NULL )&& (end = NULL));
	}
	// returns true if queue is empty
	bool empty()
	{
		return start == NULL;
	}

	// insert v at the end of the queue
	void push(T v)
	{
		node<T>* temp = new node<T>(v);
		if (empty())
		{
			start = end = temp;
		}
		else
		{
			end->next = temp;
			end = temp;
		}

	}

	// retuns the first element of the queue
	T front()
	{
		if (empty())
			return NULL;
		else
			return start->v;
	}

	// removes the first element of the queue
	void pop()
	{
		if (empty())
		{
			cout << "Queue is Empty" << endl;
		}
		else if (start == end)
		{
			// there is only 1 element in the queue
			delete start;
			start = end = NULL;
		}
		else
		{
			// if there are more than 1 element in the queue
			node<T>* temp = start;
			start = start->next;
			delete temp;
		}
	}


};