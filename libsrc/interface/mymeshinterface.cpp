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
  Ngx_MyMesh :: Ngx_MyMesh (shared_ptr<MyMesh> amesh) 
  {
    if (amesh)
      mesh = amesh;
  }

  Ngx_MyMesh :: ~Ngx_MyMesh () {}

  void Ngx_MyMesh :: LoadMesh (const string & filename) {}

  int Ngx_MyMesh :: GetNNodes1() {return 1;}
  int Ngx_MyMesh :: GetNNodes2() {return 1;}
}