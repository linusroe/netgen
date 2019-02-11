#ifndef MYMESHCLASS
#define MYMESHCLASS
#endif

#include <cstdlib>
#include <memory>
#include <vector>
//#include "../meshing/topology.hpp"

namespace netgen
{

struct MY_T_EDGE
{
    int nr;
};

class MyMesh
{
public:

    class Node
    {
    public:
        double x;
        double y;
        double z;
        std::size_t idx;
        std::vector<int> neighbors;

        Node(double x_ = 0, double y_ = 0, double z_ = 0, std::size_t idx_ = 0) :
        x{x_}, y{y_}, z{z_}, idx{idx_} {}

        std::string print() const
        {
            std::string s(std::string("V") + std::to_string(idx) + std::string(" (") +
                          std::to_string(x) + std::string(", ") + std::to_string(y) +
                          std::string(", ") + std::to_string(z) + std::string(")"));
            return s;
        }
    };

    class Edge
    {
    public:
        Node a;
        Node b;
        std::vector<int> nodeIdx;
        std::size_t idx;
        std::vector<int> neighbors;
        struct MY_T_EDGE edgestruct;

        Edge(Node a_, Node b_, std::size_t idx_ = 0) : a{a_}, b{b_}, idx{idx_} 
        {
            nodeIdx.push_back(a.idx);
            nodeIdx.push_back(b.idx);
            edgestruct.nr = idx;
        }

        std::string print() const
        {
            std::string s(std::string("E") + std::to_string(idx) + std::string(" (V") +
                          std::to_string(a.idx) + std::string(", V") +
                          std::to_string(b.idx) + std::string(")"));
            return s;
        }
    };

    class Face
    {
    public:
        std::vector<Node> nodes;
        std::vector<Edge> edges;
        std::vector<int> neighbors;
        std::size_t idx;

        Face(std::vector<Node> nodes_, std::vector<Edge> edges_, std::size_t idx_ = 0) :
        nodes{nodes_}, edges{edges_}, idx{idx_} {}

        std::string print() const
        {
            std::string s(std::string("F") + std::to_string(idx) + std::string(" (("));
            for (auto node : nodes)
                s += std::string("V") + std::to_string(node.idx) + std::string(" ");
            s += std::string("), (");

            for (auto edge : edges)
                s += std::string("E") + std::to_string(edge.idx) + std::string(" ");
            s += std::string("))");
            return s;
        }
    };

    class Volume
    {
    public:
        std::vector<Node> nodes;
        std::vector<Edge> edges;
        std::vector<Face> faces;
        std::size_t idx;

        Volume(std::vector<Node> nodes_, std::vector<Edge> edges_,
              std::vector<Face> faces_, std::size_t idx_ = 0) :
        nodes{nodes_}, edges{edges_}, faces{faces_}, idx{idx_} {}

        std::string print() const
        {
            std::string s(std::string("Vo") + std::to_string(idx) + std::string(" (("));
            for (auto node : nodes)
                s += std::string("V") + std::to_string(node.idx) + std::string(" ");
            s += std::string("), (");

            for (auto edge : edges)
                s += std::string("E") + std::to_string(edge.idx) + std::string(" ");
            s += std::string("), (");

            for (auto face : faces)
                s += std::string("F") + std::to_string(face.idx) + std::string(" ");
            s += std::string("))");
            return s;
        }
    };

private:
    std::size_t dim;
    std::size_t numNodes;
    std::size_t numEdges;
    std::size_t numFaces;
    std::size_t numVolumes;
    std::vector<Node> nodes;
    std::vector<Edge> edges;
    std::vector<Face> faces;
    std::vector<Volume> volumes;

    void computeNeighborNodes(Node &n);
    void computeNeighborEdges(Edge &e);
    void computeNeighborFaces(Face &f);

public:
    MyMesh(std::size_t dimX = 0, std::size_t dimY = 0, std::size_t dimZ = 0);

    int getDim() { return dim; }
    int getNumNodes() { return numNodes; }
    int getNumEdges() { return numEdges; }
    int getNumFaces() { return numFaces; }
    int getNumVolumes() { return numVolumes; }

    std::vector<Node> getNodes() { return nodes; }
    std::vector<Edge> getEdges() { return edges; }
    std::vector<Face> getFaces() { return faces; }
    std::vector<Volume> getVolumes() { return volumes; }
};

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
}