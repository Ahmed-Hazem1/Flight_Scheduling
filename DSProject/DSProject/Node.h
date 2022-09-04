#ifndef _NODE
#define _NODE

//First let's declare a single node in the list
template<typename T>
class Node
{
public:
	T value;	// A data item (can be any complex sturcture)
	Node<T>* next;	// Pointer to next node

	Node() //default constructor
	{
		next = nullptr;
	}

	Node(T newItem) //non-default constructor
	{
		value = newItem;
		next = nullptr;

	}

	void setItem(T newItem)
	{
		value = newItem;
	} // end setItem

	void setNext(Node<T>* nextNodePtr)
	{
		next = nextNodePtr;
	} // end setNext

	T getItem() const
	{
		return value;
	} // end getItem

	Node<T>* getNext() const
	{
		return next;
	}
}; // end Node

#endif	
