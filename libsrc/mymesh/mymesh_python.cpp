#include "../general/ngpython.hpp"
#include "mymeshclass.hpp"

#ifdef WIN32
#define DLL_HEADER __declspec(dllimport)
#else
#define DLL_HEADER
#endif

using namespace netgen;

DLL_HEADER void ExportMyMesh(py::module &m) 
{
    py::class_<MyMesh> (m, "MyMesh")
        .def(py::init<std::size_t, std::size_t, std::size_t>());

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
