#include <iostream>
#include <math.h>
#include "hashmap.h"

using namespace std;

int Hashmap::myhash(double x)
{
  x *= sizeb;
  return int(x);
}

Hashmap::Hashmap()
{
  // initial size of table
  sizeb = 800;
  // allocate table, initialize head ptrs all to NULL
  table = new Node **[sizeb];
  for (int i = 0; i < sizeb; i++)
  {
    table[i] = new Node *[sizeb];
    for (int j = 0; j < sizeb; j++)
    {
      table[i][j] = NULL;
    }
  }
}

Hashmap::~Hashmap()
{
  // delete table
  for (int i = 0; i < sizeb; i++)
  {
    for (int j = 0; j < sizeb; j++)
    {
      while (table[i][j])
      {
        Node *temp = table[i][j];
        table[i][j] = table[i][j]->next;
        delete temp;
      }
    }
    delete[] table[i];
  }
  delete[] table;
}

void Hashmap::insert(double x, double y)
{
  table[myhash(x)][myhash(y)] = new Node(x, y, table[myhash(x)][myhash(y)]);
}

double Hashmap::distanceFunc(Node *first, Node *second)
{
  //distance function
  return sqrt(pow((first->xcoord - second->xcoord), 2)
              + pow((first->ycoord - second->ycoord), 2));
}

double Hashmap::shortestDistance()
{
  double smallestDist = 1;
  //loop through x of table
  for (int i = 0; i < sizeb; i++)
  {
    //loop through y of table
    for (int j = 0; j < sizeb; j++)
    {
      //for each node
      for (Node *n = table[i][j]; n; n = n->next)
      {
        for (int x = (i-1); x < (i+1); x++)
        {
          for (int y = (j-1); y < (j+1); y++)
          {
            //check to make sure I don't escape the bounds of the array
            if ((x >= 0 && x < sizeb) && (y >= 0 && y < sizeb))
            {
              for (Node *o = table[x][y]; o; o = o->next)
              {
                //check for comparison against itself
                if (n != o)
                {
                  //swap distances if smaller
                  smallestDist = (smallestDist > distanceFunc(n, o)) ?
                    distanceFunc(n, o) : smallestDist;
                }
              }
            }
          }
        }
      }
    }
  }
  return smallestDist;
}
