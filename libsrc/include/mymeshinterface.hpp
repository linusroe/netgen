#ifndef MYMESHINTERFACE
#define MYMESHINTERFACE

//#include <memory>
//#include "nginterface.h"
//#include "nginterface_v2.hpp"
//#include "../mymesh/mymeshclass.hpp"

namespace netgen
{
  class MyMesh;

  class Ngx_MyMesh// : public Ngx_Mesh
  {
  private:
    shared_ptr<MyMesh> mesh;
  };
}

#endif
