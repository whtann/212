#include <iostream>
#include <cstdlib>
using namespace std;

// store distinct values in a hash table
struct Node
{
  int val;
  Node *next;
  Node (int v, Node *n) { val = v; next = n; }
};

Node **T;

// hash function
int myhash(int val, int table_size)
{
  unsigned int h = 0;
    h = (2917 + (unsigned int)val) % table_size;
  return h;
}

bool find(int x, int num)
{
  for (Node *n = T[x]; n != NULL; n = n->next)
    if (n->val == num) return true;
  return false;
}

int main(int argc, char *argv[])
{
  if (argc != 2) {
    cout << "Usage: bad1 <input size>\n";
    return 0;
  }

  int N = atoi(argv[1]);  // get first command-line argument
  if (N<1) {
    cout << "Invalid input size!\n";
    return 0;
  }

  // make hash table and initialize to null
  T = new Node *[N];
  for (int i = 0; i < N; i++)
    T[i] = NULL;

  cout << N << endl;
  for (int i = 0; i < N; i++)
  {
    int inserts = 0;
    while (inserts < 2)
    {
      int randnum = rand() % (10*N);
      int tempindex = myhash(randnum, N);
      if (!find(tempindex, randnum))
      {
        T[tempindex] = new Node(randnum, T[tempindex]);
        cout << randnum << " ";
        inserts++;
      }
    }
    cout << endl;
  }
}
