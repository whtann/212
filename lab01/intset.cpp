#include <iostream>
#include <assert.h>
#include "intset.h"

using namespace std;

//initializes the head to nullptr
Intset::Intset()
{
	head = nullptr;
}

//deletes all nodes in the list
Intset::~Intset()
{
	if (head)
	{
		node *temp = head;
		while (temp->next)
		{
			temp = temp->next;
			delete head;
			head = temp;
		}
	}
}

/* Return true if key is in the set */
bool Intset::find(int key)
{
	node *temp = head;

	while (temp->next)
	{
		if (temp->data == key)
		{
			return true;
		}
		else
		{
			temp = temp->next;
		}
	}
	return false;
}

/* Inserts a new key.  It is an error if key is already in the set. */
void Intset::insert(int key)
{
	assert(!find(key));
	//list check
	if (head)
	{
		node *temp = head, *newNode = new node;

		while (temp->next)
		{
			//if the key is less than the head replace it
			if (key < head->data)
			{
				newNode->next = head;
				head = newNode;
				break;
			}
			//if the key is in the middle of the list replace it
			if (temp->data < key && key < temp->next->data)
			{
				newNode->next = temp->next;
				temp->next = newNode;
				break;
			}
			//if the key is greater than the list
			if (!temp->next)
			{
				temp->next = newNode;
				break;
			}
			//iterator
			temp = temp->next;
		}
	}
	//if the list doesn't exist create it
	else
	{
		head = new node;
		head->data = key;
		head->next = nullptr;
	}
}

/* Removes a key.  It is an error if key isn't in the set */
void Intset::remove(int key)
{
	assert(find(key));
	node *temp = head, *temp2 = head;
	//if key is = to head node delete head node
	if (head->data == key)
	{
		head = head->next;
		delete temp;
	}
	else
	{
		while (temp->next)
		{
			temp = temp2->next;
			//if the node is in the middle of the list, delete it
			if (temp2->data == key)
			{
				temp->next = temp2->next;
				delete temp2;
				break;
			}
			//if the node is at the end of the list, delete it
			if (!temp2->next)
			{
				delete temp2;
				break;
			}
		}
	}
}

void Intset::print(void)
{
	if (head)
	{
		node *temp = head;
		while (temp->next)
		{
			cout << temp->data << endl;
		}
	}
}
