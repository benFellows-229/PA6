// a union find data structure

#ifndef UF_H
#define UF_H

class UF
{
public:
    UF(int size);
    ~UF();
    int find(int x);
    void Union(int x, int y);

private:
    int *id;
    int *sz;
    int size;
};
#endif
