#ifndef MYMESHCLASS
#define MYMESHCLASS
#endif

#include <cstdlib>
#include <memory>
#include <vector>

namespace netgen
{
  class MyMesh
  {
  public:
    class Node
    {
    public:
      double x;
      double y;
      double z;

      Node(double x_ = 0, double y_ = 0, double z_ = 0) :
      x{x_}, y{y_}, z{z_} {}
      std::string print() const
      {
        std::string s(std::string("(") + std::to_string(x) + std::string(", ") +
        std::to_string(y) + std::string(", ") + std::to_string(z) + std::string(")"));
        return s;
      }
    };
    class Edge
    {
    public:
      Node a;
      Node b;
      Edge(Node a_, Node b_) :
      a{a_}, b{b_} {}
      std::string print() const
      {
        std::string s(std::string("(") + a.print() + std::string(", ") +
          b.print() + std::string(")"));
        return s;
      }
    };

    class Face
    {
    public:
      std::vector<Node> nodes;
      std::vector<Edge> edges;
      Face(std::vector<Node> nodes_, std::vector<Edge> edges_) :
      nodes{nodes_}, edges{edges_} {}
    };

  private:
    int dim;
    int numNodes;
    int numEdges;
    int numFaces;
    int numVolumes;
    std::vector<Node> nodes;
    std::vector<Edge> edges;
    std::vector<Face> faces;


  public:
    MyMesh(std::size_t dimX = 0, std::size_t dimY = 0, std::size_t dimZ = 0);

    int getDim(){return dim;}
    int getNumNodes(){return numNodes;}
    int getNumEdges(){return numEdges;}
    int getNumFaces(){return numFaces;}
    int getNumVolumes(){return numVolumes;}

    std::vector<Node> getNodes(){return nodes;}
    std::vector<Edge> getEdges(){return edges;}
  };

  bool operator==(const MyMesh::Node& lhs, const MyMesh::Node& rhs)
  {
  if(lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z)
      return true;
    return false;
  }

  bool operator!=(const MyMesh::Node& lhs, const MyMesh::Node& rhs) {return !(lhs == rhs);}
  std::ostream& operator<<(std::ostream& os, const MyMesh::Node& node)
  {
    os << node.print();
    return os;
  }

  std::ostream& operator<<(std::ostream& os, const MyMesh::Edge& edge)
  {
    os << edge.print();
    return os;
  }

}