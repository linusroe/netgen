#include "mymeshclass.hpp"
#include <iostream>

int main()
{
    netgen::MyMesh m = netgen::MyMesh(5, 5, 0);
    std::cout << m.getNumNodes() << "\n";
    unsigned short x = 0;
    for(auto i : m.getNodes())
        std::cout << x++ << i << "\n";

    std::cout << m.getNumEdges() << "\n";
    for(auto i : m.getEdges())
        std::cout << i << "\n";
}