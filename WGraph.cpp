#include "WGraph.h"

WGraph::WGraph()
{
  m_size = 0;
  m_adj = NULL;
}

WGraph::WGraph(unsigned int sz)
{
  m_size = sz;
  // allocate sz * sz adj matrix
  m_adj = new double *[sz];
  m_conn = new double *[sz];
  for (int i = 0; i < m_size; ++i)
  {
    m_adj[i] = new double[sz];
    m_conn[i] = new double[sz];
  }
  // start with edges
  for (int i = 0; i < m_size; ++i)
  {
    for (int j = 0; j < m_size; ++j)
    {
      m_adj[i][j] = std::numeric_limits<double>::max();
      m_conn[i][j] = std::numeric_limits<double>::max();
    }
  }
}

WGraph::~WGraph()
{
  // release memory
  for (int i = 0; i < m_size; ++i)
  {
    delete[] m_adj[i];
    delete[] m_conn[i];
  }
}

void WGraph::addEdge(VertexID i, VertexID j, double w)
{
  if (i < m_size && j < m_size)
  {
    m_adj[i][j] = w;
    m_adj[j][i] = w;
  }
}

void WGraph::removeEdge(VertexID i, VertexID j)
{
  if (i < m_size && j < m_size)
  {
    m_adj[i][j] = std::numeric_limits<double>::max();
    m_adj[j][i] = std::numeric_limits<double>::max();
  }
}

bool WGraph::areAdjacent(VertexID i, VertexID j)
{
  return (m_adj[i][j] < std::numeric_limits<double>::max());
}

void WGraph::calcFW()
{
  for (int i = 0; i < m_size; ++i)
  {
    for (int j = 0; j < m_size; ++j)
    {
      m_conn[i][j] = m_adj[i][j]; // start with conn == adj matrix
    }
  }

  for (int im = 0; im < m_size; ++im)
  { // transitive closure
    for (int source = 0; source < m_size; ++source)
    {
      for (int sink = 0; sink < m_size; ++sink)
      {
        // every possible pair of source,sink and intermediate node
        if (source == sink)
        {
          continue;
        }
        if (m_conn[source][im] != std::numeric_limits<double>::max() &&
            m_conn[im][sink] != std::numeric_limits<double>::max() &&
            m_conn[source][sink] > m_conn[source][im] + m_conn[im][sink])
        {
          m_conn[source][sink] = m_conn[source][im] + m_conn[im][sink];
        }
      }
    }
  }
}

// find mst using kruskal's algorithm and union find
// first sort all the edges of a graph according to their edge-weight values.
// then, pick the smallest edge and check if it forms a cycle with the spanning tree formed so far.
// if cycle is not formed, include this edge. Else, discard it.
// store mst as adjacency matrix
void WGraph::computeMST()
{
  // initialize mst
  int totalWeight = 0;
  double **mst;
  mst = new double *[m_size];
  for (int i = 0; i < m_size; ++i)
  {
    mst[i] = new double[m_size];
  }
  for (int i = 0; i < m_size; ++i)
  {
    for (int j = 0; j < m_size; ++j)
    {
      mst[i][j] = 0;
    }
  }

  // create priority queue of edges
  PQueue<Edge> edgeQ(true);
  for (int i = 0; i < m_size; ++i)
  {
    for (int j = i + 1; j < m_size; ++j)
    {
      if (m_adj[i][j] < std::numeric_limits<double>::max())
      {
        if (m_adj[i][j] != 0)
        {
          edgeQ.addEdge(Edge(i, j, m_adj[i][j]));
        }
      }
    }
  }
  // create union find
  UF uf(m_size);
  // while there are edges in the queue
  while (!edgeQ.isEmpty())
  {
    // get the edge with the smallest weight
    Edge e = edgeQ.pop();
    // if the edge does not form a cycle
    if (!uf.connected(e.source, e.dest))
    {
      // addEdge the edge to the mst
      mst[e.source][e.dest] = e.weight;
      mst[e.dest][e.source] = e.weight;
      uf.Union(e.source, e.dest);
      totalWeight += e.weight;
    }
  }
  // print the mst
  cout << "MST: " << endl;
  for (int i = 0; i < m_size; ++i)
  {
    for (int j = 0; j < m_size; ++j)
    {
      cout << mst[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl
       << "Total weight: " << totalWeight << endl << endl;
}

// a method to create a graph from a file and return the graph
WGraph WGraph::processFile(string iFile)
{
  // open the file
  ifstream in;
  in.open(iFile);
  // read the number of vertices
  int numVertices;
  in >> numVertices;
  // create a graph with numVertices
  WGraph g(numVertices);
  // read the adjacency matrix
  for (int i = 0; i < numVertices; ++i)
  {
    for (int j = 0; j < numVertices; ++j)
    {
      double weight = 0;
      in >> weight;
      g.addEdge(i, j, weight);
    }
  }
  // close the file
  in.close();
  // return the graph
  return g;
}

double WGraph::cheapestCost(VertexID i, VertexID j)
{
  return m_conn[i][j];
}

// method to print adjecency matrix
void WGraph::printAdj()
{
  for (int i = 0; i < m_size; ++i)
  {
    for (int j = 0; j < m_size; ++j)
    {
      cout << m_adj[i][j] << " ";
    }
    cout << endl;
  }
}