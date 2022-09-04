#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "LinkedList.h"

using namespace std;
template<typename T>
class Queue : public LinkedList<T> {
	// no queue specific attributes needed
public:
	// common queue operations
	void enqueue(T newValue)
	{
		this->appendNode(newValue);

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
		// 2 ways to implement clear()
	// 1) we can write a loop
	//while (!isEmpty()) {
	//	dequeue();
	//}
	// 2) we can leverage the destructor 
	// code we alread wrote in LinkedList
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
		// 2 ways to implement size
	// 1) traverse the linked list and count
	// the number of nodes O(N)
	// 2) add a count/size attribute to LinkedList class
	// need to keep this up to date
	// O(1) 

	// 1)
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