#include "WGraph.h"
using namespace std;
int main(){

    WGraph g = WGraph::processFile("test.txt");
    cout << endl << "Graph:" << endl;
    g.printAdj();
    cout << endl;
    g.computeMST();
    return 0;
}