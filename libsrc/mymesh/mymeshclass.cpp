#include "mymeshclass.hpp"
#include <cmath>
#include <iostream>
#include <set>

namespace netgen
{
MyMesh ::MyMesh(std::size_t dimX,
                std::size_t dimY,
                std::size_t dimZ) :
                numNodes{0}, numEdges{0}, numFaces{0},
                numVolumes{0}, material{"default"}
{
    dim = dimX ? 1 : 0;
    dim += dimY ? 1 : 0;
    dim += dimZ ? 1 : 0;

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

                bool boundary = false;

                {
                    if (k == 0 || k == dimZ || j == 0 || j == dimY || i == 0 || i == dimX)
                        boundary = true;
                }

                if (boundary)
                {
                    Node p{i * ptStepX, j * ptStepY, k * ptStepZ, numNodes, numBndNodes};
                    p.boundary = true;
                    bnd_nodes.push_back(p);
                    numBndNodes++;
                    nodes.push_back(p);
                    numNodes++;
                }
                else
                {
                    Node p{i * ptStepX, j * ptStepY, k * ptStepZ, numNodes};
                    nodes.push_back(p);
                    numNodes++;
                }
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

                std::size_t nodepos = k * (dimY + 1) * (dimX + 1) + j * (dimX + 1) + i;

                if (i + 1 <= dimX)
                {
                    std::size_t right = k * (dimY + 1) * (dimX + 1) + j * (dimX + 1) + (i + 1);
                    if ((j == 0 || j == dimY) && (k == 0 || k == dimZ))
                    {
                        Edge e{&nodes[nodepos], &nodes[right], numEdges, numBndEdges};
                        e.boundary = true;
                        bnd_edges.push_back(e);
                        numBndEdges++;
                        edges.push_back(e);
                        numEdges++;
                    }
                    else
                    {
                        Edge e{&nodes[nodepos], &nodes[right], numEdges};
                        edges.push_back(e);
                        numEdges++;
                    }
                    
                }

                if (j + 1 <= dimY)
                {
                    std::size_t below = k * (dimY + 1) * (dimX + 1) + (j + 1) * (dimX + 1) + i;
                    if ((k == 0 || k == dimZ) && (i == 0 || i == dimX))
                    {
                        Edge e{&nodes[nodepos], &nodes[below], numEdges, numBndEdges};
                        e.boundary = true;
                        bnd_edges.push_back(e);
                        numBndEdges++;
                        edges.push_back(e);
                        numEdges++;
                    }
                    else
                    {
                        Edge e{&nodes[nodepos], &nodes[below], numEdges};
                        edges.push_back(e);
                        numEdges++;
                    }
                }

                if (k + 1 <= dimZ)
                {
                    std::size_t behind = (k + 1) * (dimY + 1) * (dimX + 1) + j * (dimX + 1) + i;
                    if ((j == 0 || j == dimY) && (i == 0 || i == dimX))
                    {
                        Edge e{&nodes[nodepos], &nodes[behind], numEdges, numBndEdges};
                        e.boundary = true;
                        bnd_edges.push_back(e);
                        numBndEdges++;
                        edges.push_back(e);
                        numEdges++;
                    }
                    else
                    {
                        Edge e{&nodes[nodepos], &nodes[behind], numEdges};
                        edges.push_back(e);
                        numEdges++;
                    }
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
                std::size_t nodepos = k * (dimY + 1) * (dimX + 1) + j * (dimX + 1) + i;

                if (i + 1 <= dimX && j + 1 <= dimY)
                {
                    std::vector<Node *> faceNodesFront;
                    std::vector<Edge *> faceEdgesFront;

                    std::size_t right = k * (dimY + 1) * (dimX + 1) + j * (dimX + 1) + (i + 1);
                    std::size_t below = k * (dimY + 1) * (dimX + 1) + (j + 1) * (dimX + 1) + i;
                    std::size_t across = k * (dimY + 1) * (dimX + 1) + (j + 1) * (dimX + 1) + (i + 1);

                    faceNodesFront.push_back(&nodes[nodepos]);
                    faceNodesFront.push_back(&nodes[right]);
                    faceNodesFront.push_back(&nodes[below]);
                    faceNodesFront.push_back(&nodes[across]);

                    for (Edge &edge : edges)
                    {
                        if (*(edge.a) == nodes[nodepos] && (*(edge.b) == nodes[right] 
                            || *(edge.b) == nodes[below]))
                                faceEdgesFront.push_back(&edge);

                        if (*(edge.a) == nodes[right] && *(edge.b) == nodes[across])
                                faceEdgesFront.push_back(&edge);

                        if (*(edge.a) == nodes[below] && *(edge.b) == nodes[across])
                                faceEdgesFront.push_back(&edge);
                    }

                    bool boundary = true;
                    for (Node *n : faceNodesFront)
                    {
                        if (!n->boundary)
                        {
                            boundary = false;
                            break;
                        }
                    }

                    if(boundary)
                    {
                        Face f{faceNodesFront, faceEdgesFront, numFaces, numBndFaces};
                        f.boundary = true;
                        bnd_faces.push_back(f);
                        numBndFaces++;
                        faces.push_back(f);
                        numFaces++;
                    }
                    else
                    {
                        Face f{faceNodesFront, faceEdgesFront, numFaces};
                        faces.push_back(f);
                        numFaces++;
                    }
                }

                if (i + 1 <= dimX && k + 1 <= dimZ)
                {
                    std::vector<Node *> faceNodesTop;
                    std::vector<Edge *> faceEdgesTop;

                    std::size_t right = k * (dimY + 1) * (dimX + 1) + j * (dimX + 1) + i + 1;
                    std::size_t behind = (k + 1) * (dimY + 1) * (dimX + 1) + j * (dimX + 1) + i;
                    std::size_t across = (k + 1) * (dimY + 1) * (dimX + 1) + j * (dimX + 1) + i + 1;

                    faceNodesTop.push_back(&nodes[nodepos]);
                    faceNodesTop.push_back(&nodes[right]);
                    faceNodesTop.push_back(&nodes[behind]);
                    faceNodesTop.push_back(&nodes[across]);

                    for (Edge &edge : edges)
                    {
                        if (*(edge.a) == nodes[nodepos] && (*(edge.b) == nodes[right] 
                            || *(edge.b) == nodes[behind]))
                            faceEdgesTop.push_back(&edge);
                        if (*(edge.a) == nodes[right] && *(edge.b) == nodes[across])
                            faceEdgesTop.push_back(&edge);
                        if (*(edge.a) == nodes[behind] && *(edge.b) == nodes[across])
                            faceEdgesTop.push_back(&edge);
                    }

                    bool boundary = true;
                    for (Node *n : faceNodesTop)
                    {
                        if (!n->boundary)
                        {
                            boundary = false;
                            break;
                        }
                    }

                    if(boundary)
                    {
                        Face f{faceNodesTop, faceEdgesTop, numFaces, numBndFaces};
                        f.boundary = true;
                        bnd_faces.push_back(f);
                        numBndFaces++;
                        faces.push_back(f);
                        numFaces++;
                    }
                    else
                    {
                        Face f{faceNodesTop, faceEdgesTop, numFaces};
                        faces.push_back(f);
                        numFaces++;
                    }
                }

                if (j + 1 <= dimY && k + 1 <= dimZ)
                {
                    std::vector<Node *> faceNodesSide;
                    std::vector<Edge *> faceEdgesSide;

                    std::size_t below = k * (dimY + 1) * (dimX + 1) + (j + 1) * (dimX + 1) + i;
                    std::size_t behind = (k + 1) * (dimY + 1) * (dimX + 1) + j * (dimX + 1) + i;
                    std::size_t across = (k + 1) * (dimY + 1) * (dimX + 1) + (j + 1) * (dimX + 1) + i;

                    faceNodesSide.push_back(&nodes[nodepos]);
                    faceNodesSide.push_back(&nodes[below]);
                    faceNodesSide.push_back(&nodes[behind]);
                    faceNodesSide.push_back(&nodes[across]);

                    for (Edge &edge : edges)
                    {
                        if (*(edge.a) == nodes[nodepos] && (*(edge.b) == nodes[below] 
                            || *(edge.b) == nodes[behind]))
                            faceEdgesSide.push_back(&edge);
                        if (*(edge.a) == nodes[below] && *(edge.b) == nodes[across])
                            faceEdgesSide.push_back(&edge);
                        if (*(edge.a) == nodes[behind] && *(edge.b) == nodes[across])
                            faceEdgesSide.push_back(&edge);
                    }


                    bool boundary = true;
                    for (Node *n : faceNodesSide)
                    {
                        if (!n->boundary)
                        {
                            boundary = false;
                            break;
                        }
                    }

                    if(boundary)
                    {
                        Face f{faceNodesSide, faceEdgesSide, numFaces, numBndFaces};
                        f.boundary = true;
                        bnd_faces.push_back(f);
                        numBndFaces++;
                        faces.push_back(f);
                        numFaces++;
                    }
                    else
                    {
                        Face f{faceNodesSide, faceEdgesSide, numFaces};
                        faces.push_back(f);
                        numFaces++;
                    }
                }
            }
        }
    }
    //Compute Volumes
    for (std::size_t k = 0; k < dimZ; ++k)
    {
        for (std::size_t j = 0; j < dimY; ++j)
        {
            for (std::size_t i = 0; i < dimX; ++i)
            {

                std::vector<Node *> volNodes;
                for (std::size_t l = 0; l < 2; ++l)
                {
                    for (std::size_t m = 0; m < 2; ++m)
                    {
                        for (std::size_t n = 0; n < 2; ++n)
                        {
                            std::size_t idx = (k + l) * (dimY + 1) * (dimX + 1) 
                                            + (j + m) * (dimX + 1) + (i + n);
                            volNodes.push_back(&nodes[idx]);
                        }
                    }
                }

                std::vector<Edge *> volEdges;
                for (Edge &e : edges)
                {
                    if (*(e.a) == *volNodes[0] && (*(e.b) == *volNodes[1] ||
                        *(e.b) == *volNodes[2] || *(e.b) == *volNodes[4]))
                        volEdges.push_back(&e);

                    if (*(e.a) == *volNodes[1] && (*(e.b) == *volNodes[3] ||
                        *(e.b) ==*volNodes[5]))
                        volEdges.push_back(&e);

                    if (*(e.a) == *volNodes[2] && (*(e.b) == *volNodes[3] ||
                        *(e.b) ==*volNodes[6]))
                        volEdges.push_back(&e);

                    if (*(e.a) == *volNodes[3] && *(e.b) == *volNodes[7])
                        volEdges.push_back(&e);

                    if (*(e.a) == *volNodes[4] && (*(e.b) == *volNodes[5] ||
                        *(e.b) ==*volNodes[6]))
                        volEdges.push_back(&e);

                    if (*(e.a) == *volNodes[5] && *(e.b) == *volNodes[7])
                        volEdges.push_back(&e);

                    if (*(e.a) == *volNodes[6] && *(e.b) == *volNodes[7])
                        volEdges.push_back(&e);
                }

                std::vector<Face *> volFaces;
                for (Face &f : faces)
                {
                    if (*(f.nodes[0]) == *volNodes[0])
                        volFaces.push_back(&f);

                    if (*(f.nodes[0]) == *volNodes[1] &&
                        *(f.nodes[1]) == *volNodes[3] &&
                        *(f.nodes[2]) == *volNodes[5])
                        volFaces.push_back(&f);

                    if (*(f.nodes[0]) == *volNodes[2] &&
                        *(f.nodes[1]) == *volNodes[3] &&
                        *(f.nodes[2]) == *volNodes[6])
                        volFaces.push_back(&f);

                    if (*(f.nodes[0]) == *volNodes[4] &&
                        *(f.nodes[1]) == *volNodes[5] &&
                        *(f.nodes[2]) == *volNodes[6])
                        volFaces.push_back(&f);
                }

                Volume v{volNodes, volEdges, volFaces, numVolumes};
                ++numVolumes;
                volumes.push_back(v);
            }
        }
    }

    if (dim == 3)
    {
        for (Volume &v : volumes)
        {
            for (Node *n : v.nodes)
                n->partOfElement.push_back(static_cast<int>(v.idx));
        }

        for (Face &f : faces)
        {
            for (Node *n : f.nodes)
                n->partOfBndElement.push_back(static_cast<int>(f.idx));
        }
    }

    if (dim == 2)
    {
        for (Face &f : faces)
        {
            for (Node *n : f.nodes)
                n->partOfElement.push_back(static_cast<int>(f.idx));
        }

        for (Edge &e : edges)
        {
                e.a->partOfBndElement.push_back(static_cast<int>(e.idx));
                e.b->partOfBndElement.push_back(static_cast<int>(e.idx));
        }
    }
}

MyMesh::Node::Node(double x_, double y_, double z_,
                    std::size_t idx_, std::size_t bnd_idx_) :
    x{x_}, y{y_}, z{z_}, idx{idx_}, bnd_idx{bnd_idx_} 
{
        coord.push_back(x);
        coord.push_back(y);
        coord.push_back(z);
}

std::string MyMesh::Node::print() const
{
    std::string s(std::string("V") + std::to_string(idx) + std::string(" (") +
                    std::to_string(x) + std::string(", ") + std::to_string(y) +
                    std::string(", ") + std::to_string(z) + std::string(")"));
    return s;
}

MyMesh::Edge::Edge(Node *a_, Node *b_, std::size_t idx_, std::size_t bnd_idx_) : 
    a{a_}, b{b_}, idx{idx_}, bnd_idx{bnd_idx_}
{
    nodeIdx.push_back(static_cast<int>(a->idx));
    nodeIdx.push_back(static_cast<int>(b->idx));
    edgestruct.nr = static_cast<int>(idx);
    if (a->boundary && b->boundary)
        boundary = true;
}

std::string MyMesh::Edge::print() const
{
    std::string s(std::string("E") + std::to_string(idx) + std::string(" (V") +
                    std::to_string(a->idx) + std::string(", V") +
                    std::to_string(b->idx) + std::string(")"));
    return s;
}

MyMesh::Face::Face(std::vector<Node *> nodes_, std::vector<Edge *> edges_,
                    std::size_t idx_, std::size_t bnd_idx_) :
    nodes{nodes_}, edges{edges_}, idx{idx_}, bnd_idx{bnd_idx_}
{
    for (Node *node : nodes)
        nodeIdx.push_back(static_cast<int>(node->idx));

    bool checkboundary = true;
    for (Edge *edge : edges)
    {
        t_edges.push_back(edge->edgestruct);
        edgeIdx.push_back(static_cast<int>(edge->idx));

        if (checkboundary && !edge->boundary)
            checkboundary = false;
    }
    boundary = checkboundary;

    facestruct.nr = static_cast<int>(idx);
}

std::string MyMesh::Face::print() const
{
    std::string s(std::string("F") + std::to_string(idx) + std::string(" (("));
    for (Node *node : nodes)
        s += std::string("V") + std::to_string(node->idx) + std::string(" ");
    s += std::string("), (");

    for (Edge *edge : edges)
        s += std::string("E") + std::to_string(edge->idx) + std::string(" ");
    s += std::string("))");
    return s;
}

MyMesh::Volume::Volume(std::vector<Node *> nodes_, std::vector<Edge *> edges_,
                        std::vector<Face *> faces_, std::size_t idx_) :
    nodes{nodes_}, edges{edges_}, faces{faces_}, idx{idx_} 
{
    for (Node *n : nodes)
        nodeIdx.push_back(static_cast<int>(n->idx));

    for (Edge *e : edges)
        t_edges.push_back(e->edgestruct);

    for (Face *f : faces)
    {
        t_faces.push_back(f->facestruct);

        if (f->boundary)
            boundary = true;
    }
}

std::string MyMesh::Volume::print() const
{
    std::string s(std::string("Vo") + std::to_string(idx) + std::string(" (("));
    for (Node *node : nodes)
        s += std::string("V") + std::to_string(node->idx) + std::string(" ");
    s += std::string("), (");

    for (Edge *edge : edges)
        s += std::string("E") + std::to_string(edge->idx) + std::string(" ");
    s += std::string("), (");

    for (Face *face : faces)
        s += std::string("F") + std::to_string(face->idx) + std::string(" ");
    s += std::string("))");
    return s;
}

int MyMesh::getDim() { return dim; }
int MyMesh::getNumNodes() { return numNodes; }
int MyMesh::getNumEdges() { return numEdges; }
int MyMesh::getNumFaces() { return numFaces; }
int MyMesh::getNumVolumes() { return numVolumes; }

std::vector<MyMesh::Node> &MyMesh::getNodes() { return nodes; }
std::vector<MyMesh::Edge> &MyMesh::getEdges() { return edges; }
std::vector<MyMesh::Face> &MyMesh::getFaces() { return faces; }
std::vector<MyMesh::Volume> &MyMesh::getVolumes() { return volumes; }

int MyMesh::getNumBndNodes() { return numBndNodes; }
int MyMesh::getNumBndEdges() { return numBndEdges; }
int MyMesh::getNumBndFaces() { return numBndFaces; }

std::vector<MyMesh::Node> MyMesh::getBndNodes() { return bnd_nodes; }
std::vector<MyMesh::Edge> MyMesh::getBndEdges() { return bnd_edges; }
std::vector<MyMesh::Face> MyMesh::getBndFaces() { return bnd_faces; }

std::string &MyMesh::getMaterial()
{
    return material;
}

bool operator==(const MyMesh::Node &lhs, const MyMesh::Node &rhs)
{
    if (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z)
        return true;
    return false;
}

bool operator!=(const MyMesh::Node &lhs, const MyMesh::Node &rhs) { return !(lhs == rhs); }

std::ostream &operator<<(std::ostream &os, const MyMesh::Node &node)
{
    os << node.print();
    return os;
}

std::ostream &operator<<(std::ostream &os, const MyMesh::Edge &edge)
{
    os << edge.print();
    return os;
}

std::ostream &operator<<(std::ostream &os, const MyMesh::Face &face)
{
    os << face.print();
    return os;
}

std::ostream &operator<<(std::ostream &os, const MyMesh::Volume &volume)
{
    os << volume.print();
    return os;
}

} // namespace netgen
