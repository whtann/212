#include <iostream>
#include <string.h>
#include <assert.h>
#include "stringset.h"

using namespace std;

/* Return a hash for the string s in the range 0..table_size-1 */
int myhash(string s, int table_size)
{
  unsigned int i, h = 0;
  for (i=0; i<s.length(); i++)
    h = (h * 2917 + (unsigned int)s[i]) % table_size;
  return h;
}

Stringset::Stringset()
{
  size = 4; // initial size of table
  table = new Node *[size]; // allocate table, initialize head ptrs all to NULL
  for (int i=0; i<size; i++)
    table[i] = NULL;
  num_elems = 0;
}

Stringset::~Stringset()
{
  for (int i=0; i<size; i++) {
    while (table[i] != NULL) {
      Node *temp = table[i];
      table[i] = table[i]->next;
      delete temp;
    }
  }
  delete[] table;
}

/* Return true if key is in the set */
bool Stringset::find(string key)
{
  int h = myhash(key, size);
  Node *n = table[h];
  while (n != NULL) {
    if (n->key == key) return true;
    n = n->next;
  }
  return false;
}

/* Inserts a new key.  It is an error if key is already in the set. */
void Stringset::insert(string key)
{
  assert (!find(key));
  num_elems++;

  if (num_elems == size) {
    // TBD: Expand table -- allocate new table of twice the size,
    // re-insert all keys into new table, and de-allocate old table.
    // (you may want to wait and add this code last, once everything
    // else is working, since the class will still function properly,
    // albeit slowly, without this part)
    size = size * 2;
    //create new table & initialize to 0
    Node **newTable = new Node *[size];
    for (int i=0; i<size; i++)
    {
      newTable[i] = NULL;
    }
    //look for nodes in old hash table
    for (int i = 0; i<(size/2); i++)
    {
      Node *temp = table[i];
      //remove multiple nodes at one index of the old table
      while (table[i])
      {
        int hashnum = myhash(table[i]->key, size);
        //rehash into the new table
        newTable[hashnum] = new Node(table[i]->key, newTable[hashnum]);
        //continue to the rest of the nodes
        table[i] = table[i]->next;
        delete temp;
        temp = table[i];
      }
    }
    //delete old table and reassign new table
    delete [] table;
    table = newTable;
  }

  // TBD: Insert new element
  int hashnum = myhash(key, size);
  table[hashnum] = new Node(key, table[hashnum]);
}

/* Removes a key.  It is an error if key isn't in the set */
void Stringset::remove(string key)
{
  assert (find(key));
  num_elems--;

  // TBD: Delete element
  int hashnum = myhash(key, size);
  Node *temp = table[hashnum];
  //check to remove head
  if (table[hashnum]->key == key)
  {
    table[hashnum] = table[hashnum]->next;
    delete temp;
  }
  //check if the node is in the linked list of the index
  else
  {
    Node *temp2 = temp->next;
    while (temp2)
    {
      if (temp2->key == key)
      {
        temp->next = temp2->next;
        delete temp2;
      }
      temp = temp2;
      temp2 = temp->next;
    }
  }
}

void Stringset::print(void)
{
  // TBD: Print contents of table
  for (int i = 0; i<size; i++)
  {
    Node *temp = table[i];
    while (temp)
    {
      cout << temp->key << endl;
      temp = temp->next;
    }
  }
}
