#ifndef MYMESHCLASS
#define MYMESHCLASS
#endif

#include <memory>

namespace netgen
{
  class MyMesh
  {
  private:
    int dim;
    int numNodes;
    int numEdges;
    int numFaces;
    int numVolumes;

  public:
    MyMesh(std::size_t dimX = 0, std::size_t dimY = 0, std::size_t dimZ = 0)
    : dim{0}
    {
    }

    int getDim(){return dim;}
    int getNumNodes(){return numNodes;}
    int getNumEdges(){return numEdges;}
    int getNumFaces(){return numFaces;}
    int getNumVolumes(){return numVolumes;}
  };
}