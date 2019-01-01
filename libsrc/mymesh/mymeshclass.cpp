#include "mymeshclass.hpp"
#include <iostream>
#include <cmath>

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

    for (std::size_t k = 0; k <= dimZ; ++k)
    {
        for (std::size_t j = 0; j <= dimY; ++j)
        {
            for (std::size_t i = 0; i <= dimX; ++i)
            {
                Node p{i*ptStepX, j*ptStepY, k*ptStepZ};
                nodes.push_back(p);
                numNodes++;
            }
        }
    }

    for (std::size_t k = 0; k <= dimZ; ++k)
    {
        for (std::size_t j = 0; j <= dimY; ++j)
        {
            for (std::size_t i = 0; i <= dimX; ++i)
            { 
                std::size_t nodepos = k * (dimZ + 1) * (dimY + 1) + j * (dimX + 1) + i;

                if(i + 1 <= dimX)
                { 
                    std::size_t right = k * (dimY + 1) * (dimX + 1) + j * (dimX + 1) + i + 1;
                    Edge e{nodes[nodepos], nodes[right]};
                    edges.push_back(e);
                    numEdges++;
                }

                if(j + 1  <= dimY)
                { 
                    std::size_t below = k * (dimY + 1) * (dimX + 1) + (j + 1) * (dimX + 1) + i;
                    Edge e{nodes[nodepos], nodes[below]};
                    edges.push_back(e);
                    numEdges++;
                }

                if(k + 1 <= dimZ)
                { 
                    std::size_t behind = (k + 1) * (dimY + 1) * (dimX + 1) + j * (dimX + 1) + i;
                    Edge e{nodes[nodepos], nodes[behind]};
                    edges.push_back(e);
                    numEdges++;
                }
            }
        }   
    }
}
}
