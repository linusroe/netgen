#ifdef NG_PYTHON

#include "../general/ngpython.hpp"
#include "mymeshclass.hpp"

#include <meshing.hpp>
#include "nginterface.h"
#include "../include/nginterface_v2.hpp"

using namespace netgen;

// Exposes C++ mesh to python
DLL_HEADER void ExportMyMesh(py::module &m)
{
    py::class_<Ngx_Mesh,shared_ptr<Ngx_Mesh>> (m, "Ngx_Mesh");

    py::class_<MyMesh,shared_ptr<MyMesh>> (m, "MyMesh")
        .def(py::init<std::size_t, std::size_t, std::size_t>());

    py::class_<Ngx_MyMesh,shared_ptr<Ngx_MyMesh>,Ngx_Mesh> (m, "Ngx_MyMesh")
        .def(py::init<shared_ptr<MyMesh>>());
}

PYBIND11_MODULE(libmesh, m) {
  ExportMyMesh(m);
}

#endif
