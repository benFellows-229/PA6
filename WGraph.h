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
// an unweighted, undirected WGraph implemented with adjacency matrix
// fixed size

typedef unsigned int VertexID;

// structure to keep track of the source and destination nodes, as well as their weight.
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
  Edge(VertexID s, VertexID d, double w)
  {
    source = s;
    dest = d;
    weight = w;
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
