#include <iostream>
#include <assert.h>
#include "intset.h"

using namespace std;

Intset::Intset()
{
  head = nullptr;
}

Intset::~Intset()
{
  if (head) {
    node *temp = head;
    while (temp->next) {
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
  
    while (temp->next) {
	if (temp->data == key) { return true }
	else {
	    temp = temp->next;
	}
    }
    return false;
}

/* Inserts a new key.  It is an error if key is already in the set. */
void Intset::insert(int key)
{
    assert (!find(key));
    node *temp = head, node *newNode = new node;
    while (temp->next) {
	if (key < head) {
	    newNode->next = head;
	    head = newNode;
	    break;
	}
	if (temp->data < key && key < temp->next->data) {
	    newNode->next = temp->next;
	    temp->next = newNode;
	    break;
	}
	if (!temp->next) {
	    temp->next = newNode;
	    break;
	}
	temp = temp->next;
    }
}

/* Removes a key.  It is an error if key isn't in the set */
void Intset::remove(int key)
{
    assert (find(key));
    node *temp = node *temp2 = head;
    if (head->data == key) {
	head = head->next;
	delete temp;
    }
    else {
	while (temp->next) {
	    temp = temp2->next;
	    if (temp2->data == key) {
		temp->next = temp2->next;
		delete temp2;
		break;
	    }
	    if (!temp2->next) {
		delete temp2;
		break;
	    }

}

void Intset::print(void)
{
  int i;
  for (i=0; i<size; i++)
    cout << A[i] << "\n";
}
