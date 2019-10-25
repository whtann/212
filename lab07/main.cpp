#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <set>
#include <math.h>
using namespace std;

typedef pair<double, double> Point;

double distanceFunc(Point first, Point second)
{
  //distance function w/o sqrt
  return sqrt(pow((first.first - second.first), 2)
          + pow((first.second - second.second), 2));
}

double distFuncRev(Point first, Point second)
{
  //distance function w/o sqrt
  return sqrt(pow((first.second - second.first), 2)
          + pow((first.first - second.second), 2));
}

int main()
{
  //declare vector variables
  double x, y;
  vector<Point> v;
  //scan points
  ifstream infile("points.txt");
  while (infile >> x >> y) { v.push_back(make_pair(x, y)); }
  infile.close();
  //sort points on x
  sort(v.begin(), v.end());
  //declare set variables
  double D = distanceFunc(v[0], v[1]);
  set<Point> s;
  int i = 0;
  set<Point>::iterator it;
  double tempD;
  //advance j
  for (unsigned int j = 0; j < v.size(); j++)
  {
    s.insert(make_pair(v[j].second, v[j].first));
    //advance i
    while ((v[j].first - v[i].first) > D)
    {
      s.erase(Point(v[i].second, v[i].first));
      i++;
    }
    //base point
    it = s.find(Point(v[j].second, v[j].first));
    //Successor check
    while (1)
    {
      it++;
      if (it == s.end()) { break; }
      if ((it->first - v[j].second) < D)
      {
        tempD = distFuncRev(*it, v[j]);
        if (tempD < D) { D = tempD; }
      }
    }
    //reset to base
    it = s.find(Point(v[j].second, v[j].first));
    //Predecessor check
    while (1)
    {
      it--;
      //check the beginning point but break the loop after
      if (it == s.begin())
      {
        if (*it != Point(v[j].second, v[j].first) &&
           (v[j].second - it->first) < D)
        {
          tempD = distFuncRev(*it, v[j]);
          if (tempD < D) { D = tempD; }
        }
        break;
      }
      //normal check
      if ((v[j].second - it->first) < D)
      {
        tempD = distFuncRev(*it, v[j]);
        if (tempD < D) { D = tempD; }
      }
    }
  }
  cout << D << " is the shortest distance." << endl;
  return 0;
}
