#ifndef HASHMAP_H
#define HASHMAP_H

using namespace std;

class Hashmap
{
private:
  struct Node
  {
    double xcoord;
    double ycoord;
    Node* next;
    Node(double x, double y, Node *n) { xcoord = x; ycoord = y; next = n; }
    Node() { xcoord = 0; ycoord = 0; next = NULL; }
  };

  Node ***table;
  int sizeb;

public:
  Hashmap();
  ~Hashmap();
  int myhash(double x);
  void insert(double x, double y);
  double distanceFunc(Node *first, Node *second);
  double shortestDistance();
};

#endif
