#include "mymeshclass.hpp"
#include <cmath>
#include <iostream>

namespace netgen
{
MyMesh ::MyMesh(std::size_t dimX,
                std::size_t dimY,
                std::size_t dimZ) : numNodes{0}, numEdges{0}, numFaces{0}, numVolumes{0}
{
    double ptStepX = dimX ? 1.0 / dimX : 0;
    double ptStepY = dimY ? 1.0 / dimY : 0;
    double ptStepZ = dimZ ? 1.0 / dimZ : 0;

    //Compute Nodes
    for (std::size_t k = 0; k <= dimZ; ++k)
    {
        for (std::size_t j = 0; j <= dimY; ++j)
        {
            for (std::size_t i = 0; i <= dimX; ++i)
            {
                Node p{i * ptStepX, j * ptStepY, k * ptStepZ, numNodes};
                nodes.push_back(p);
                numNodes++;
            }
        }
    }

    //Compute Edges
    for (std::size_t k = 0; k <= dimZ; ++k)
    {
        for (std::size_t j = 0; j <= dimY; ++j)
        {
            for (std::size_t i = 0; i <= dimX; ++i)
            {
                std::size_t nodepos = k * (dimZ + 1) * (dimY + 1) + j * (dimX + 1) + i;

                if (i + 1 <= dimX)
                {
                    std::size_t right = k * (dimY + 1) * (dimX + 1) + j * (dimX + 1) + i + 1;
                    Edge e{nodes[nodepos], nodes[right], numEdges};
                    edges.push_back(e);
                    numEdges++;
                }

                if (j + 1 <= dimY)
                {
                    std::size_t below = k * (dimY + 1) * (dimX + 1) + (j + 1) * (dimX + 1) + i;
                    Edge e{nodes[nodepos], nodes[below], numEdges};
                    edges.push_back(e);
                    numEdges++;
                }

                if (k + 1 <= dimZ)
                {
                    std::size_t behind = (k + 1) * (dimY + 1) * (dimX + 1) + j * (dimX + 1) + i;
                    Edge e{nodes[nodepos], nodes[behind], numEdges};
                    edges.push_back(e);
                    numEdges++;
                }
            }
        }
    }

    //Compute Faces
    for (std::size_t k = 0; k <= dimZ; ++k)
    {
        for (std::size_t j = 0; j <= dimY; ++j)
        {
            for (std::size_t i = 0; i <= dimX; ++i)
            {
                std::size_t nodepos = k * (dimZ + 1) * (dimY + 1) + j * (dimX + 1) + i;

                if (i + 1 <= dimX && j + 1 <= dimY)
                {
                    std::vector<Node> faceNodesFront;
                    std::vector<Edge> faceEdgesFront;

                    std::size_t right = k * (dimY + 1) * (dimX + 1) + j * (dimX + 1) + i + 1;
                    std::size_t below = k * (dimY + 1) * (dimX + 1) + (j + 1) * (dimX + 1) + i;
                    std::size_t across = k * (dimY + 1) * (dimX + 1) + (j + 1) * (dimX + 1) + i + 1;

                    faceNodesFront.push_back(nodes[nodepos]);
                    faceNodesFront.push_back(nodes[right]);
                    faceNodesFront.push_back(nodes[below]);
                    faceNodesFront.push_back(nodes[across]);

                    for (auto edge : edges)
                    {
                        if (edge.a == nodes[nodepos] && (edge.b == nodes[right] || edge.b == nodes[below]))
                            faceEdgesFront.push_back(edge);
                        if (edge.a == nodes[right] && edge.b == nodes[across])
                            faceEdgesFront.push_back(edge);
                        if (edge.a == nodes[below] && edge.b == nodes[across])
                            faceEdgesFront.push_back(edge);
                    }

                    Face f{faceNodesFront, faceEdgesFront, numFaces};
                    faces.push_back(f);
                    numFaces++;
                }

                if (i + 1 <= dimX && k + 1 <= dimZ)
                {
                    std::vector<Node> faceNodesTop;
                    std::vector<Edge> faceEdgesTop;

                    std::size_t right = k * (dimY + 1) * (dimX + 1) + j * (dimX + 1) + i + 1;
                    std::size_t behind = (k + 1) * (dimY + 1) * (dimX + 1) + j * (dimX + 1) + i;
                    std::size_t across = (k + 1) * (dimY + 1) * (dimX + 1) + j * (dimX + 1) + i + 1;

                    faceNodesTop.push_back(nodes[nodepos]);
                    faceNodesTop.push_back(nodes[right]);
                    faceNodesTop.push_back(nodes[behind]);
                    faceNodesTop.push_back(nodes[across]);

                    for (auto edge : edges)
                    {
                        if (edge.a == nodes[nodepos] && (edge.b == nodes[right] || edge.b == nodes[behind]))
                            faceEdgesTop.push_back(edge);
                        if (edge.a == nodes[right] && edge.b == nodes[across])
                            faceEdgesTop.push_back(edge);
                        if (edge.a == nodes[behind] && edge.b == nodes[across])
                            faceEdgesTop.push_back(edge);
                    }

                    Face f{faceNodesTop, faceEdgesTop, numFaces};
                    faces.push_back(f);
                    numFaces++;
                }

                if (j + 1 <= dimY && k + 1 <= dimZ)
                {
                    std::vector<Node> faceNodesSide;
                    std::vector<Edge> faceEdgesSide;

                    std::size_t below = k * (dimY + 1) * (dimX + 1) + (j + 1) * (dimX + 1) + i;
                    std::size_t behind = (k + 1) * (dimY + 1) * (dimX + 1) + j * (dimX + 1) + i;
                    std::size_t across = (k + 1) * (dimY + 1) * (dimX + 1) + (j + 1) * (dimX + 1) + i;

                    faceNodesSide.push_back(nodes[nodepos]);
                    faceNodesSide.push_back(nodes[below]);
                    faceNodesSide.push_back(nodes[behind]);
                    faceNodesSide.push_back(nodes[across]);

                    for (auto edge : edges)
                    {
                        if (edge.a == nodes[nodepos] && (edge.b == nodes[below] || edge.b == nodes[behind]))
                            faceEdgesSide.push_back(edge);
                        if (edge.a == nodes[below] && edge.b == nodes[across])
                            faceEdgesSide.push_back(edge);
                        if (edge.a == nodes[behind] && edge.b == nodes[across])
                            faceEdgesSide.push_back(edge);
                    }

                    Face f{faceNodesSide, faceEdgesSide, numFaces};
                    faces.push_back(f);
                    numFaces++;
                }
            }
        }
    }
}
} // namespace netgen
