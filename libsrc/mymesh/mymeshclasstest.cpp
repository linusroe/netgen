#include "mymeshclass.hpp"
#include <iostream>
#include <meshing.hpp>
#include <nginterface.h>
#include <nginterface_v2.hpp>

int main()
{
    auto spm = make_shared<netgen::MyMesh>(3, 3, 3);
    netgen::MyMesh & m(*spm);
    std::cout << "Number of Nodes:" << m.getNumNodes() << "\n";
    for (auto i : m.getNodes())
    { 
        std::cout << i << " at boundary " << i.boundary << "\n";
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
        std::cout << i << " at boundary " << i.boundary << "\n";
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
        std::cout << i << " at boundary " << i.boundary << "\n";
        std::cout << "Number of neighbors: " << 
                    i.neighbors.size() << "\n";
        for(auto j : i.neighbors)
            std::cout << j << " ";
        std::cout << "\n\n";
    }

    std::cout << "\n----------------\n\n";
    std::cout << "Number of Volumes: " <<  m.getNumVolumes() << "\n";
    for (auto i : m.getVolumes())
    {
        std::cout << i << " at boundary " << i.boundary << "\n";
        std::cout << "Number of neighbors: " << 
                    i.neighbors.size() << "\n";
        for(auto j : i.neighbors)
            std::cout << j << " ";
        std::cout << "\n\n";
    }
    


    std::cout << "\n\n\n---------Testing Interface-------\n\n";
    netgen::Ngx_MyMesh ngsmym(spm);
    std::cout << ngsmym.GetDimension() << "\n";
}
