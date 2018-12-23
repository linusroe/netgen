#include <mystdlib.h>
#include <mymeshinterface.hpp>
#include <mymesh.hpp>

#include <meshing.hpp>
#include "writeuser.hpp"

#ifdef SOCKETS
#include "../sockets/sockets.hpp"
#endif

#include "nginterface.h"
#include "nginterface_v2.hpp"


namespace netgen
{
  Ngx_MyMesh :: Ngx_MyMesh(shared_ptr<MyMesh> amesh) 
  {
    if (amesh)
      mesh = amesh;
  }

  Ngx_MyMesh :: ~Ngx_MyMesh() {}

  void Ngx_MyMesh :: LoadMesh(const string & filename) {}

  void Ngx_MyMesh :: LoadMesh (istream & str) {}
  void Ngx_MyMesh :: SaveMesh (ostream & str) const {}
  void Ngx_MyMesh :: UpdateTopology () {}
  void Ngx_MyMesh :: DoArchive (ngstd::Archive & archive) {}

  int Ngx_MyMesh :: GetDimension() const {return mesh->getDim();}
  int Ngx_MyMesh :: GetNLevels() const {return 0;}

  int Ngx_MyMesh :: GetNElements(int dim) const {return -1;}

  int Ngx_MyMesh :: GetNNodes(int nt) const 
  {
    switch (nt)
    {
      case 0: return mesh->getNumNodes();
      case 1: return mesh->getNumEdges();
      case 2: return mesh->getNumEdges();
      case 3: return mesh->getNumVolumes();
      default: return -1;
    }
  }

  int Ngx_MyMesh :: GetNNodes1() {return mesh->getNumNodes();}
  int Ngx_MyMesh :: GetNNodes2() {return mesh->getNumEdges();}
}