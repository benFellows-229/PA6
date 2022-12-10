/*
Ben Fellows
002369768
bfellows@chapman.edu
CPSC-350-02
CPSC350 PA6
main.cpp
A cpp file containing a main method which creates a WGraph object and calls the computeMST method.
*/
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