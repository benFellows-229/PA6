#ifndef UF_H
#define UF_H

class UF
{
public:
    UF(int size);
    ~UF();
    int find(int x);
    void Union(int x, int y);
    bool connected(int x, int y);

private:
    int *parent;
    int *sz;
    int size;
};
#endif
