/*
Ben Fellows
002369768
bfellows@chapman.edu
CPSC-350-02
CPSC350 PA6
UF.cpp
A cpp file containing a Union Find disjoint set class.
*/

#include "UF.h"

//Constructor initializes all values to their own index as each vertex is its own set, and each size is initialized to 1
UF::UF(int size)
{
    this->size = size;
    parent = new int[size];
    sz = new int[size];
    for (int i = 0; i < size; ++i)
    {
        parent[i] = i;
        sz[i] = 1;
    }
}

UF::~UF()
{
    delete[] parent;
    delete[] sz;
}
// find method to find the root of a vertex
int UF::find(int x)
{
    int i = x;
    while (i != parent[i])
        i = parent[i];

    while (x != i)
    {
        int j = parent[x];
        parent[x] = i;
        x = j;
    }

    return i;
}
// Union method to join two sets, checks the size of each set and sets the smaller sets root = to the larger sets root
void UF::Union(int x, int y)
{
    int i = find(x);
    int j = find(y);
    if (i == j)
        return;
    if (sz[i] < sz[j])
    {
        parent[i] = j;
        sz[j] += sz[i];
    }
    else
    {
        parent[j] = i;
        sz[i] += sz[j];
    }
}

// connected method to check if two vertices are in the same set, checks by calling find on each vertex and checking if their roots are equal.
bool UF::connected(int x, int y)
{
    return find(x) == find(y);
}
