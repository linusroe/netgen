#ifdef NG_PYTHON

#include "../general/ngpython.hpp"
#include "mymeshclass.hpp"

#include <meshing.hpp>
// #include "nginterface.h"
#include "nginterface.h"
#include "../include/nginterface_v2.hpp"
// #include <meshing.hpp>

using namespace netgen;

DLL_HEADER void ExportMyMesh(py::module &m) 
{
    py::class_<Ngx_Mesh,shared_ptr<Ngx_Mesh>> (m, "Ngx_Mesh");
    //.def(py::init<std::size_t, std::size_t, std::size_t>());

    py::class_<MyMesh,shared_ptr<MyMesh>> (m, "MyMesh")
        .def(py::init<std::size_t, std::size_t, std::size_t>());

    py::class_<Ngx_MyMesh,shared_ptr<Ngx_MyMesh>,Ngx_Mesh> (m, "Ngx_MyMesh")
        .def(py::init<shared_ptr<MyMesh>>());
    
    py::class_<MyMesh::Node> (m, "Node")
        .def("__str__", &MyMesh::Node::print);

    py::class_<MyMesh::Edge> (m, "Edge")
        .def("__str__", &MyMesh::Edge::print);

    py::class_<MyMesh::Face> (m, "Face")
        .def("__str__", &MyMesh::Face::print);

    py::class_<MyMesh::Volume> (m, "Volume")
        .def("__str__", &MyMesh::Volume::print);
}

PYBIND11_MODULE(libmesh, m) {
  ExportMyMesh(m);
}

#endif
