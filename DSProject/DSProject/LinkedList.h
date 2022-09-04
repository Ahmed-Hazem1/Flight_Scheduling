#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <iostream>

using namespace std;


template<typename T>
class LinkedList
{
public:
	Node<T>* head; // list head pointer
	Node<T>* tail; // list tail pointer

	//template<typename T>
	LinkedList()
	{

		head = NULL;
		tail = NULL;
	}
	LinkedList(Node<T>* head)
	{
		this->head = head;
		tail = head;
	}
	
	// DVC
	~LinkedList()
	{
		destroyList();

	}// destructor

	// common linked list operations
	void displayList() 
	{
		Node<T>* currNode = head;

		cout << "head->";
		while (currNode != NULL) {
			cout << currNode->value << "->";
			// progress towards BC being false
			currNode = currNode->next;
		}
		cout << "NULL" << endl;
		if (tail != NULL) {
			cout << "tail->" << tail->value << endl;
		}
		else {
			cout << "tail->NULL" << endl;
		}
	}
	void appendNode(T newValue)
	{
		// make a new Node
		Node<T>* newNode = new Node<T>;
		newNode->value = newValue;
		newNode->next = NULL;

		// 2 cases
		if (head == NULL) {
			head = newNode;
			tail = head;
		}
		else {
			// list is not empty
			tail = newNode;
			tail->next = NULL;
		}
	} // insert at end
	T deleteAtFront()
	{
		// check to make sure there is something to delete
		T value = NULL;
		if (head != NULL) {
			Node<T>* nodeToDelete = head;
			head = head->next;
			value = nodeToDelete->value;
			delete nodeToDelete;
			if (head == NULL) {
				tail = NULL;
			}
		}
		return value;
	}
	void destroyList()
	{
		// TODO: free each Node's memory in the list
		Node<T>* currNode = new Node<T>;
		currNode = head;
		Node<T>* nextNode = NULL;

		while (currNode != NULL) {
			// save the link to the next node
			nextNode = currNode->next;
			// can safely delete currNode
			delete currNode;
			currNode = nextNode;
		}
		head = NULL; // for good practice
		tail = NULL;
	}
	void insertInOrder(T newValue)
	{
		// make a new Node
		Node<T>* newNode = new Node<T>;
		newNode->value = newValue;
		newNode->next = NULL;

		// 2 cases
		if (head == NULL) {
			head = newNode;
			tail = newNode;
		}
		else {
			// list is not empty
			Node<T>* currNode = head;
			Node<T>* prevNode = NULL;

			while (currNode != NULL && currNode->value > newValue) {
				prevNode = currNode;
				currNode = currNode->next;
			}

			// 2 cases to check
			// 1) inserting at head... so we didn't advance currNode (therefore prevNode is NULL)
			// 2) inserting somewhere other than the head, need to the splicing
			if (prevNode == NULL) {
				head = newNode;
				newNode->next = currNode;
			}
			else {
				prevNode->next = newNode;
				newNode->next = currNode;
				if (newNode->next == NULL) {
					// new last node in the list
					tail = newNode;
				}
			}
		}
	}
};

#endif