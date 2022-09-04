#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include <iostream>
#include "LinkedList.h"

using namespace std;

template<typename T>
class PriorityQueue : public LinkedList<T>
{
public:
	void enqueue(T newValue)
	{
		this->insertInOrder(newValue);
	}
	T dequeue()
	{
		return LinkedList<T>::deleteAtFront();

	}
	T peek()
	{
		if (LinkedList<T>::head != NULL) {
			return LinkedList<T>::head->value;
		}
		return NULL;
	}
	void clear()
	{
		LinkedList<T>::destroyList();
	}
	bool isEmpty()
	{
		if (LinkedList<T>::head != NULL)
		{
			return false;
		}
		return true;
	}
	int size()
	{



		int count = 0;
		Node* currNode = LinkedList<T>::head;
		while (currNode != NULL) {
			count++;
			currNode = currNode->next;
		}
		return count;
	}
};


#endif