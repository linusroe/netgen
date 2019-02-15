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

    py::class_<MyMesh::Node> (m, "Node");

    py::class_<MyMesh::Edge> (m, "Edge");

    py::class_<MyMesh::Face> (m, "Face");

    py::class_<MyMesh::Volume> (m, "Volume");
}


