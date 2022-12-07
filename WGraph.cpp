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

//method to sort the edges in ascending order
bool compareEdges(Edge e1, Edge e2)
{
  return e1.weight < e2.weight;
}

//find mst using kruskal's algorithm and union find
//Sort all the edges of a graph according to their edge-weight values.
//output the total weight of the mst
//output the adjacency matrix of the mst
void WGraph::computeMST()
{
  // sort edges
  sort(m_edges.begin(), m_edges.end(), compareEdges);
  // create a set of vertices
  set<VertexID> vertices;
  for (int i = 0; i < m_size; ++i)
  {
   vertices.insert(i);
  }
  // create a set of edges
  set<Edge> mst;
  for (int i = 0; i < m_edges.size(); ++i)
  {
   if (vertices.find(m_edges[i].source) != vertices.end() &&
       vertices.find(m_edges[i].dest) != vertices.end())
   {
     mst.insert(m_edges[i]);
     vertices.erase(m_edges[i].source);
     vertices.erase(m_edges[i].dest);
   }
  }
  // print mst
  for (set<Edge>::iterator it = mst.begin(); it != mst.end(); ++it)
  {
   cout << it->source << " " << it->dest << " " << it->weight << endl;
  }
}



  WGraph WGraph::processFile(string iFile)
  {
    string data;
    ifstream infile(iFile);
    istringstream ss(data);
    int i = 0;
    int j = 0;
    double k = 0;
    if (infile.is_open())
    {
      WGraph tempGraph(i);
      i++;
      while (infile >> k)
      {
        cout << k << endl;
        j++;
        tempGraph.addEdge(i, j, k);
        }
    }
}

double WGraph::cheapestCost(VertexID i, VertexID j)
{
  return m_conn[i][j];
}