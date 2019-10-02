#include <iostream>
#include <algorithm>
using namespace std;

//array node
struct Student
{
  int position;
  int height;
  Student() { position = 0; height = 0; }
};

//tree node
struct Node {
  int key;
  int size;
  Node *left;
  Node *right;
  Node (int k) { key = k; size = 1; left = right = NULL; }
};

//sort operator overload
bool operator< (const Student &A, const Student &B)
{
  //return whether A's height is less than B's height
  return A.height > B.height;
}

// split on tree
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

// balanced insert
Node *insert(Node *T, int k)
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
    if (k < T->key) { T->left = insert(T->left, k); }
    else { T->right = insert(T->right, k); }
    T->size++;
    return T;
  }
}

//finds predicessor
Node *predfind(Node *root, int x)
{
  if (!root) { return NULL; }
  if (x == root->key) { return root; }
  if (x < root->key) { return predfind(root->left, x); }
  else
  {
    Node *temp = predfind(root->right, x);
    return (temp ? temp : root);
  }
}

//finds successor
Node *succfind(Node *root, int x)
{
  if (!root) { return NULL; }
  if (x == root->key) { return root; }
  if (x < root->key)
  {
    Node *temp = succfind(root->left, x);
    return (temp ? temp : root);
  }
  else { return succfind(root->right, x); }
}

int main()
{
  // get size
  int N;
  if (!(cin >> N) || N < 1)
  {
    cout << "Invalid Input Size!" << endl;
    return 0;
  }
  // read input into array
  Student *S = new Student[N];
  for (int i=0; i<N; i++)
  {
    if (!(cin >> S[i].position) || S[i].position<0)
    {
      cout << "Invalid input!" << endl;
      return 0;
    }
    if (!(cin >> S[i].height) || S[i].height<0)
    {
      cout << "Invalid input!" << endl;
      return 0;
    }
  }
  // sort array
  sort(S, (S + N));
  //create tree
  Node *Tree = NULL;
  for (int i = 0; i < N; i++)
  {
    //find successor & predicessor of every element
    Node *temppred = predfind(Tree, S[i].position);
    Node *tempsucc = succfind(Tree, S[i].position);
    //print successor or predicessor if they exist, otherwise print -1
    cout << (temppred ? (S[i].position - (temppred->key)) : -1) << " ";
    cout << (tempsucc ? ((tempsucc->key) - S[i].position) : -1) << endl;
    //insert into tree
    Tree = insert(Tree, S[i].position);
  }

  return 0;
}
