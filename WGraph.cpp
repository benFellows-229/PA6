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

//find mst using kruskal's algorithm and union find
//Sort all the edges of a graph according to their edge-weight values.
//output the total weight of the mst
//output the adjacency matrix of the mst


//a method to computeMST using Kruskal's algorithm and union find data structure
// void WGraph::computeMST()
// {
//   //create a set of edges
//   UF uf(m_size);
//   //create array of edges to sort
//   Edge *edges = new Edge[m_size];
//   for (int i = 0; i < m_size; ++i)
//   {
//     for (int j = 0; j < m_size; ++j)
//     {
//       if (m_adj[i][j] != std::numeric_limits<double>::max())
//       {
//         Edge e;
//         e.source = i;
//         e.dest = j;
//         e.weight = m_adj[i][j];
//         edges[i] = e;
//       }
//     }
//   //output the total weight of the mst
//   //output the adjacency matrix of the mst
//   }
// }


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
        cout << "j: " << j << " i: " << i << " k: " << k << endl;
        j++;
        tempGraph.addEdge(i, j, k);
        }
    }
}

double WGraph::cheapestCost(VertexID i, VertexID j)
{
  return m_conn[i][j];
}

//method to print adjecency matrix
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