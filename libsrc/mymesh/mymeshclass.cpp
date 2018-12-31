#include "mymeshclass.hpp"

namespace netgen
{
MyMesh :: MyMesh(std::size_t dimX,
                std::size_t dimY,
                std::size_t dimZ) :
                numNodes{0}, numEdges{0}, numFaces{0}, numVolumes{0}
{
    double ptStepX = dimX ? 1.0/dimX : 0; 
    double ptStepY = dimY ? 1.0/dimY : 0; 
    double ptStepZ = dimZ ? 1.0/dimZ : 0; 

    for (std::size_t i = 0; i <= dimX; ++i)
    {
        for (std::size_t j = 0; j <= dimY; ++j)
        {
            for (std::size_t k = 0; k <= dimZ; ++k)
            {
                Node p{i*ptStepX, j*ptStepY, k*ptStepZ};
                nodes.push_back(p);
                numNodes++;
            }
        }
    }

    for (std::size_t i = 0; i < getNumNodes(); ++i)
    {
        for (std::size_t j = i + 1; j < getNumNodes(); ++j)
        {
            double diffX = std::abs(nodes[i].x - nodes[j].x);
            double diffY = std::abs(nodes[i].y - nodes[j].y);
            double diffZ = std::abs(nodes[i].z - nodes[j].z);
            if(diffX <= ptStepX && diffY <= ptStepY && diffZ <= ptStepZ)
                {
                    short total = diffX == ptStepX ? 1 : 0;
                    total += diffY == ptStepY ? 1 : 0; 
                    total += diffZ == ptStepZ ? 1 : 0; 

                    if(total == 1)
                    { 
                        Edge e{nodes[i], nodes[j]};
                        edges.push_back(e);
                        numEdges++;
                    }
                }
        }
    }
}
}
