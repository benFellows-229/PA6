#ifndef WGraph_H
#define WGraph_H

#include <cstdlib>
#include <deque>
#include <set>
#include <stack>
#include <iostream>
#include <limits>
#include <fstream>
#include "UF.h"
#include "PQueue.h"
using namespace std;

typedef unsigned int VertexID;

// Edge structure to keep track of the source and destination nodes, as well as their weight.
struct Edge
{
  VertexID source;
  VertexID dest;
  double weight;
  // default constructor
  Edge()
  {
    source = 0;
    dest = 0;
    weight = 0;
  }
  //overloaded constructor
  Edge(VertexID s, VertexID d, double w)
  {
    source = s;
    dest = d;
    weight = w;
  }
  //overloaded operators to compare weights of edges
  friend bool operator<(const Edge &e1, const Edge &e2)
  {
    return e1.weight < e2.weight;
  }
  friend bool operator>(const Edge &e1, const Edge &e2)
  {
    return e1.weight > e2.weight;
  }
};

class WGraph
{
public:
  WGraph();
  WGraph(unsigned int sz);
  ~WGraph();
  void addEdge(VertexID i, VertexID j, double w);
  void removeEdge(VertexID i, VertexID j);
  bool areAdjacent(VertexID i, VertexID j);
  double cheapestCost(VertexID i, VertexID j);
  void calcFW();
  static WGraph processFile(string iFile);
  void computeMST();
  void printAdj();

private:
  double **m_adj;
  double **m_conn;
  unsigned int m_size; // nodes in WGraph (fixed)
};

#endif
