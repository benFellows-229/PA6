// a union find data structure

#include "UF.h"

UF::UF(int size)
{
    this->size = size;
    id = new int[size];
    sz = new int[size];
    for (int i = 0; i < size; ++i)
    {
        id[i] = i;
        sz[i] = 1;
    }
}

UF::~UF()
{
    delete[] id;
    delete[] sz;
}

int UF::find(int x)
{
    int i = x;
    while (i != id[i])
        i = id[i];

    while (x != i)
    {
        int j = id[x];
        id[x] = i;
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
        id[i] = j;
        sz[j] += sz[i];
    }
    else
    {
        id[j] = i;
        sz[i] += sz[j];
    }
}

// connected method to check if two vertices are connected
bool UF::connected(int x, int y)
{
    return find(x) == find(y);
}
