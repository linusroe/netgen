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

    for (Node from : nodes)
    {
        for(Node to : nodes)
        {
            if(from != to && ((from.x - to.x <= ptStepX)  && dimX ||
               (from.y - to.y <= ptStepY) && dimY || (from.z - to.z <= ptStepZ) && dimZ))
                {
                    Edge e{from, to};
                    edges.push_back(e);
                    numEdges++;
                }
        }
    }
}
}
