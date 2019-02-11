#include "mymeshclass.hpp"
#include <iostream>

int main()
{
    netgen::MyMesh m = netgen::MyMesh(2, 3, 0);
    std::cout << "Number of Nodes:" << m.getNumNodes() << "\n";
    unsigned short x = 0;
    for (auto i : m.getNodes())
    { 
        std::cout << i << "\n";
        std::cout << "Number of neighbors: " << 
                    i.neighbors.size() << "\n";
        for(auto j : i.neighbors)
            std::cout << j << " ";
        std::cout << "\n\n";
    }

    std::cout << "\n----------------\n\n";
    std::cout << "Number of Edges: " << m.getNumEdges() << "\n";
    for (auto i : m.getEdges())
    {
        std::cout << i << "\n";
        std::cout << "Number of neighbors: " << 
                    i.neighbors.size() << "\n";
        for(auto j : i.neighbors)
            std::cout << j << " ";
        std::cout << "\n\n";
    }

    std::cout << "\n----------------\n\n";
    std::cout << "Number of Faces: " <<  m.getNumFaces() << "\n";
    for (auto i : m.getFaces())
    {
        std::cout << i << "\n";
        std::cout << "Number of neighbors: " << 
                    i.neighbors.size() << "\n";
        for(auto j : i.neighbors)
            std::cout << j << " ";
        std::cout << "\n\n";
    }

    std::cout << m.getNumVolumes() << "\n";
    for (auto i : m.getVolumes())
        std::cout << i << "\n";
}