#include "mymeshclass.hpp"
#include <iostream>

int main()
{
    netgen::MyMesh m = netgen::MyMesh(2, 2, 2);
    std::cout << m.getNumNodes() << "\n";
    for(auto i : m.getNodes())
        std::cout << i << "\n";

    std::cout << m.getNumEdges() << "\n";
    for(auto i : m.getEdges())
        std::cout << i << "\n";
}