#include <iostream>
#include <assert.h>
#include "intset.h"

using namespace std;

//initializes the head to NULL
Intset::Intset()
{
	head = NULL;
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
	if (head) {
		while (temp)
		{
			if (temp->data == key)
			{
				return true;
			}
			temp = temp->next;
		}
		return false;
	}
	else {
		return false;
	}
}

/* Inserts a new key.  It is an error if key is already in the set. */
void Intset::insert(int key)
{
	assert(!find(key));
	//list check
	if (head)
	{
		node *temp = head, *newNode = new node;
		newNode->data = key;
		newNode->next = NULL;

		//if the key is less than the head replace it
		if (key < head->data)
		{
			newNode->next = head;
			head = newNode;
		}
		else {
			while (temp)
			{
				//if the key is greater than the list
				if (!temp->next)
				{
					temp->next = newNode;
					break;
				}
				//if the key is in the middle of the list replace it
				if (temp->data < key && key < temp->next->data)
				{
					newNode->next = temp->next;
					temp->next = newNode;
					break;
				}
				//iterator
				temp = temp->next;
			}
		}
	}
	//if the list doesn't exist create it
	else
	{
		head = new node;
		head->data = key;
		head->next = NULL;
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
		if (head->next) {
			head = head->next;
			delete temp;
		}
		else
		{
			delete temp;
			head = NULL;
		}
	}
	else
	{
		while (temp)
		{
			temp = temp2->next;
			//if the node is in the middle of the list, delete it
			if (temp->data == key)
			{
				temp2->next = temp->next;
				delete temp;
				break;
			}
			//if the node is at the end of the list, delete it
			if (!temp->next)
			{
				delete temp;
				break;
			}
			temp2 = temp;
		}
	}
}

void Intset::print(void)
{
	if (head)
	{
		node *temp = head;
		while (temp)
		{
			cout << temp->data << endl;
			temp = temp->next;
		}
	}
}
