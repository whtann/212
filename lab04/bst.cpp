#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <assert.h>

using namespace std;

struct Node {
  int key;
  int size;
  Node *left;
  Node *right;
  Node (int k) { key = k; size = 1; left = right = NULL; }
};

// insert key k into tree T, returning a pointer to the resulting tree
Node *insert(Node *T, int k)
{
  // We covered this in lecture, but please make sure the code still makes sense to you...
  if (!T) return new Node(k);
  if (k < T->key) { T->left = insert(T->left, k); }
  else { T->right = insert(T->right, k); }
  T->size++;
  return T;
}

// prints out the inorder traversal of T (i.e., the contents of T in sorted order)
void print_inorder(Node *T)
{
  // We covered this in lecture, but please make sure the code still makes sense to you...
  if (!T) return;
  print_inorder(T->left);
  cout << T->key << endl;
  print_inorder(T->right);
}

// return a pointer to the node with key k in tree T, or NULL if it doesn't exist
Node *find(Node *T, int k)
{
  // We covered this in lecture, but please make sure the code still makes sense to you...
  if (!T) return NULL;
  if (k == T->key) return T;
  return (k < T->key) ? find(T->left, k) : find(T->right, k);
}

// Join trees L and R (with L containing keys all <= the keys in R)
// Return a pointer to the joined tree.
Node *join(Node *L, Node *R)
{
  // choose either the root of L or the root of R to be the root of the joined tree
  // (where we choose with probabilities proportional to the sizes of L and R)
  if (!L) return R;
  if (!R) return L;
  Node *newT = NULL;
  // random selection of L or R
  int totalSize = L->size + R->size;
  if (rand() % totalSize < L->size) { newT = L; }
  else { newT = R; }
  // size change and joins
  if (newT == L)
  {
    newT->size += R->size;
    L->right = join(L->right, R);
  }
  else
  {
    R->size += L->size;
    R->left = join(L, R->left);
  }

  return newT;
}

// remove key k from T, returning a pointer to the resulting tree.
// it is required that k be present in T
Node *remove(Node *T, int k)
{
  assert (find(T,k) != NULL);

  // get to node with recursion
  if (k < T->key) { T->left = remove(T->left, k); }
  else if (k > T->key) { T->right = remove(T->right, k); }

  // once on the node delete it
  else
  {
    Node *temp = join(T->left, T->right);
    delete T;
    return temp;
  }
}

// Split tree T on key k into tree L (containing keys <= k) and a tree R (containing keys > k)
void split(Node *T, int k, Node **L, Node **R)
{
  // base
  if (T == NULL) { *L = NULL; *R = NULL; return; }
  // tree of nodes less and equal
  if (k < T->key)
  {
    split(T->left, k, L, &T->left);
    *R = T;
    if (*L != NULL) { T->size -= (*L)->size; }
   }
   // tree of nodes greater
  else
  {
    split(T->right, k, &T->right, R);
    *L = T;
    if (*R != NULL) { T->size -= (*R)->size; }
  }
}

// insert key k into the tree T, returning a pointer to the resulting tree
// keep the tree balanced by using randomized balancing:
//  if N represents the size of our tree after the insert, then
//  with probability 1/N, insert k at the root of T (this will require splitting T on k)
//  otherwise recursively call insert_keep_balanced on the left or right, as usual
Node *insert_keep_balanced(Node *T, int k)
{
  // base case
  if (!T) { return new Node(k); }
  // rebalance
  if (rand() % (T->size + 1) == 0)
  {
    Node *newR = new Node(k);
    split(T, k, &newR->left, &newR->right);
    if (newR->left) { newR->size += newR->left->size; }
    if (newR->right) { newR->size += newR->right->size; }
    return newR;
  }
  // normal insert
  else
  {
    if (k < T->key) { T->left = insert_keep_balanced(T->left, k); }
    else { T->right = insert_keep_balanced(T->right, k); }
    T->size++;
    return T;
  }
}

int main(void)
{
  // Testing insert and print_inorder
  int A[10];

  // put 0..9 into A[0..9] in random order
  for (int i=0; i<10; i++) A[i] = i;
  for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);

  // insert contents of A into a BST
  Node *T = NULL;
  for (int i=0; i<10; i++) T = insert(T, A[i]);

  // print contents of BST (should be 0..9 in sorted order)
  cout << "\nTesting insert and print_inorder (should be 0...9):\n";
  print_inorder(T);
  cout << "Size (should be 10): " << (T ? T-> size : 0) << "\n";

  // test find: Elements 0..9 should be found; 10 should not be found
  cout << "\nTesting find (should be 1-9 found, 10 not found) \n";
  for (int i=0; i<11; i++)
    if (find(T,i)) cout << i << " found\n";
    else cout << i << " not found\n";

  // test split
  cout << "\nTesting split\n";
  Node *L, *R;
  split(T, 2, &L, &R);
  cout << "Contents of left tree after split (should be 0..2):\n";
  print_inorder(L);
  cout << "\nSize left subtree (should be 3): " << L->size << "\n";
  cout << "Contents of right tree after split (should be 3..9):\n";
  print_inorder(R);
  cout << "\nSize right subtree (should be 7): " << R->size << "\n";

  // test join
  T = join(L, R);
  cout << "\nTesting join\n";
  cout << "Contents of re-joined tree (should be 0..9)\n";
  print_inorder(T);
  cout << "\nSize (should be 10): " << T->size<< "\n";

  // test remove
  cout << "\nTesting remove\n";
  for (int i=0; i<10; i++) A[i] = i;
  for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);
  for (int i=0; i<10; i++) {
    T = remove(T, A[i]);
    cout << "Contents of tree after removing " << A[i] << ":\n";
    print_inorder(T);
    if (i < 2) {
      cout << "\nSize of tree after this removal (should be 1 less than before): " << (T ? T-> size : 0);
    }
    cout << "\n";
  }
  int size = T ? T->size : 0;
  cout << "Size (should be 0): " << size << "\n";

  // test insert_keep_balanced basic functionality
  // insert contents of A into a BST
  for (int i=0; i<10; i++) T = insert_keep_balanced(T, A[i]);

  // print contents of BST
  cout << "\n" << "Testing insert_keep_balanced (should be 0..9)\n";
  print_inorder(T);
  cout << "\n" << "Size (should be 10): " << T->size << "\n";

  // test insert_keep_balanced speed
  cout << "Inserting 10 million elements in order; this should be very fast if insert_balance is working...\n";
  for (int i=0; i<10000000; i++) T = insert_keep_balanced(T, i+10); // 10 million ints starting at 10
  cout << "Done\n";
  cout << "Size (should be 10000010): " << T->size << "\n\n";

  return 0;
}
