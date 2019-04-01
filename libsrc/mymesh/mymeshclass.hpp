#pragma once

#include <cstdlib>
#include <memory>
#include <vector>

namespace netgen
{

struct MY_T_EDGE
{
    int nr;
};

struct MY_T_FACE
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
        std::vector<double> coord;

        std::size_t idx;
        std::size_t bnd_idx;
        bool boundary = false;

        std::vector<int> partOfElement;
        std::vector<int> partOfBndElement;


        Node(double x_ = 0, double y_ = 0, double z_ = 0,
            std::size_t idx_ = 0, std::size_t bnd_idx_ = -1);

        std::string print() const;
    };

    class Edge
    {
    public:
        Node *a;
        Node *b;

        bool boundary = false;
        std::vector<int> nodeIdx;

        std::size_t idx;
        std::size_t bnd_idx;

        struct MY_T_EDGE edgestruct;

        Edge(Node *a_, Node *b_, std::size_t idx_ = 0, std::size_t bnd_idx_ = -1);

        std::string print() const;
    };

    class Face
    {
    public:
        std::vector<Node *> nodes;
        std::vector<int> nodeIdx;

        std::vector<Edge *> edges;
        std::vector<int> edgeIdx;
        std::vector<struct MY_T_EDGE> t_edges;

        bool boundary = false;

        std::size_t idx;
        std::size_t bnd_idx;

        struct MY_T_FACE facestruct;

        Face(std::vector<Node *> nodes_, std::vector<Edge *> edges_,
            std::size_t idx_ = 0, std::size_t bnd_idx_ = -1);

        std::string print() const;
    };

    class Volume
    {
    public:
        std::vector<Node *> nodes;
        std::vector<int> nodeIdx;

        std::vector<Edge *> edges;
        std::vector<struct MY_T_EDGE> t_edges;

        std::vector<Face *> faces;
        std::vector<struct MY_T_FACE> t_faces;

        bool boundary = false;
        std::size_t idx;

        Volume(std::vector<Node *> nodes_, std::vector<Edge *> edges_,
                std::vector<Face *> faces_, std::size_t idx_ = 0);

        std::string print() const;
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

    std::size_t numBndNodes = 0;
    std::size_t numBndEdges = 0;
    std::size_t numBndFaces = 0;

    std::vector<Node> bnd_nodes;
    std::vector<Edge> bnd_edges;
    std::vector<Face> bnd_faces;

    std::string material;

public:
    MyMesh(std::size_t dimX = 0, std::size_t dimY = 0, std::size_t dimZ = 0);

    int getDim();
    int getNumNodes();
    int getNumEdges();
    int getNumFaces();
    int getNumVolumes();

    std::vector<Node> &getNodes();
    std::vector<Edge> &getEdges();
    std::vector<Face> &getFaces();
    std::vector<Volume> &getVolumes();

    int getNumBndNodes();
    int getNumBndEdges();
    int getNumBndFaces();
    std::vector<Node> getBndNodes();
    std::vector<Edge> getBndEdges();
    std::vector<Face> getBndFaces();

    std::string &getMaterial();
};

bool operator==(const MyMesh::Node &lhs, const MyMesh::Node &rhs);
bool operator!=(const MyMesh::Node &lhs, const MyMesh::Node &rhs);
std::ostream &operator<<(std::ostream &os, const MyMesh::Node &node);
std::ostream &operator<<(std::ostream &os, const MyMesh::Edge &edge);
std::ostream &operator<<(std::ostream &os, const MyMesh::Face &face);
std::ostream &operator<<(std::ostream &os, const MyMesh::Volume &volume);

}
