// a union find data structure

#include "UF.h"

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

// connected method to check if two vertices are in the same set
bool UF::connected(int x, int y)
{
    return find(x) == find(y);
}
