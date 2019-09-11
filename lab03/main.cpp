#include <iostream>
#include <fstream>
#include "hashmap.h"

using namespace std;

int main(void)
{
  //create variables
  Hashmap H;
  double xcoord;
  double ycoord;

  //open file and scan data in
  ifstream pointsfile("points.txt");
  while (pointsfile >> xcoord >> ycoord)
    H.insert(xcoord, ycoord);
  pointsfile.close();

  //run calculation and print
  double shortest = H.shortestDistance();
  cout << "The Shortest Distance between two points is: " << shortest << endl;
}
