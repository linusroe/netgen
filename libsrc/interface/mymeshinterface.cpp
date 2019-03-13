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
Ngx_MyMesh ::Ngx_MyMesh(shared_ptr<MyMesh> amesh)
{
    if (amesh)
        mesh = amesh;
}

Ngx_MyMesh ::~Ngx_MyMesh() {}

void Ngx_MyMesh ::LoadMesh(const string &filename) {}

void Ngx_MyMesh ::LoadMesh(istream &str) {}
void Ngx_MyMesh ::SaveMesh(ostream &str) const {}
void Ngx_MyMesh ::UpdateTopology() {}
void Ngx_MyMesh ::DoArchive(ngstd::Archive &archive) {}

int Ngx_MyMesh ::GetDimension() const { return mesh->getDim(); }
int Ngx_MyMesh ::GetNLevels() const { return 0; }

int Ngx_MyMesh ::GetNElements(int dim) const
{
    switch (dim)
    {
    case 0:
        return mesh->getNumBndNodes();
    case 1:
        return mesh->getNumBndEdges();
    case 2:
        return mesh->getNumBndFaces();
    case 3:
        //Same as volumes in 3d case?!
        return mesh->getNumVolumes();
    default:
        return -1;
    }
}

int Ngx_MyMesh ::GetNNodes(int nt) const
{
    switch (nt)
    {
    case 0:
        return mesh->getNumNodes();
    case 1:
        return mesh->getNumEdges();
    case 2:
        return mesh->getNumFaces();
    case 3:
        return mesh->getNumVolumes();
    default:
        return -1;
    }
}

Ng_Point Ngx_MyMesh ::GetPoint(int nr) const
{
    std::size_t dim = mesh->getDim();

    double points[dim];
    if (dim >= 1)
        points[0] = mesh->getNodes()[nr].x;
    if (dim >= 2)
        points[1] = mesh->getNodes()[nr].y;
    if (dim >= 3)
        points[2] = mesh->getNodes()[nr].z;
    return Ng_Point(points);
}

int Ngx_MyMesh ::GetElementIndex0(size_t nr) const { return 1; }
int Ngx_MyMesh ::GetElementIndex1(size_t nr) const { return 1; }
//Needs to be properly implemented
int Ngx_MyMesh ::GetElementIndex2(size_t nr) const { return 11; }
int Ngx_MyMesh ::GetElementIndex3(size_t nr) const { return 0; }

Ng_Element Ngx_MyMesh ::GetElement0(size_t nr) const
{
    const MyMesh::Node &node = mesh->getNodes()[nr];

    Ng_Element ret;
    ret.type = NG_PNT;
    ret.index = 1;

    ret.points.num = 1;
    ret.points.ptr = reinterpret_cast<const int *>(&node.idx);

    ret.vertices.num = 1;
    ret.vertices.ptr = reinterpret_cast<const int *>(&node.idx);

    ret.edges.num = 0;
    ret.edges.ptr = nullptr;

    ret.faces.num = 0;
    ret.faces.ptr = nullptr;

    ret.facets.num = 1;
    ret.facets.base = 1;
    ret.facets.ptr = reinterpret_cast<const int *>(&node.idx);

    return ret;
}

Ng_Element Ngx_MyMesh ::GetElement1(size_t nr) const
{
    Ng_Element ret;
    ret.type = NG_SEGM;
    ret.index = 1;

    ret.points.num = 2;
    ret.points.ptr = &(mesh->getEdges()[nr].nodeIdx[0]);

    ret.vertices.num = 2;
    ret.vertices.ptr = &mesh->getEdges()[nr].nodeIdx[0];

    ret.edges.num = 1;
    ret.edges.ptr = reinterpret_cast<const T_EDGE2 *>(&mesh->getEdges()[nr].edgestruct);

    ret.faces.num = 0;
    ret.faces.ptr = nullptr;

    if (mesh->getDim() == 2)
    {
        ret.facets.num = 1;
        ret.facets.base = 0;
        ret.facets.ptr = (int*)ret.edges.ptr;
    }
    else
    {
        ret.facets.num = 2;
        ret.facets.base = 0;
        ret.facets.ptr = &mesh->getEdges()[nr].nodeIdx[0];
    }

    return ret;
}

Ng_Element Ngx_MyMesh ::GetElement2(size_t nr) const
{
    const MyMesh::Face &face = mesh->getFaces()[nr];

    Ng_Element ret;
    ret.type = NG_QUAD;
    ret.index = 1;

    ret.points.num = 4;
    ret.points.ptr = &face.nodeIdx[0];

    ret.vertices.num = 4;
    ret.vertices.ptr = &face.nodeIdx[0];

    ret.edges.num = 4;
    ret.edges.ptr = reinterpret_cast<const T_EDGE2 *>(&face.t_edges[0]);

    ret.faces.num = 1;
    ret.faces.ptr = reinterpret_cast<const T_FACE2 *>(&face.facestruct);

    if (mesh->getDim() == 3)
    {
        ret.facets.num = 1;
        ret.facets.base = 0;
        ret.facets.ptr = (int*)ret.faces.ptr;
    }
    else
    {
        ret.facets.num = 4;
        ret.facets.base = 0;
        ret.facets.ptr = (int*)ret.edges.ptr;
    }
    
    ret.is_curved = false;

    return ret;
}

Ng_Element Ngx_MyMesh ::GetElement3(size_t nr) const 
{
    const MyMesh::Volume &volume = mesh->getVolumes()[nr];
    
    Ng_Element ret;
    ret.type = NG_HEX;
    ret.index = 1;

    ret.points.num = 8;
    ret.points.ptr = &volume.nodeIdx[0];

    ret.vertices.num = 8;
    ret.vertices.ptr = &volume.nodeIdx[0];

    ret.edges.num = 12;
    ret.edges.ptr = reinterpret_cast<const T_EDGE2 *>(&volume.t_edges[0]);

    ret.faces.num = 6;
    ret.faces.ptr = reinterpret_cast<const T_FACE2 *>(&volume.t_faces[0]);

    ret.facets.num = 6;
    ret.facets.base = 0;
    ret.facets.ptr = (int*)ret.faces.ptr;

    ret.is_curved = false;
    return ret;
}

const string &Ngx_MyMesh ::GetMaterialCD0(int region_nr) const { return mesh->getMaterial(); };
const string &Ngx_MyMesh ::GetMaterialCD1(int region_nr) const { return mesh->getMaterial(); };
const string &Ngx_MyMesh ::GetMaterialCD2(int region_nr) const { return mesh->getMaterial(); };
const string &Ngx_MyMesh ::GetMaterialCD3(int region_nr) const { return mesh->getMaterial(); };

void Ngx_MyMesh ::ElementTransformation3x3(int elnr,
                                           const double *xi,
                                           double *x,
                                           double *dxdxi) const {};

void Ngx_MyMesh ::ElementTransformation2x3(int elnr,
                                           const double *xi,
                                           double *x,
                                           double *dxdxi) const {};

void Ngx_MyMesh ::ElementTransformation1x3(int elnr,
                                           const double *xi,
                                           double *x,
                                           double *dxdxi) const {};

void Ngx_MyMesh ::ElementTransformation0x3(int elnr,
                                           const double *xi,
                                           double *x,
                                           double *dxdxi) const {};

void Ngx_MyMesh ::ElementTransformation2x2(int elnr,
                                           const double *xi,
                                           double *x,
                                           double *dxdxi) const {};

void Ngx_MyMesh ::ElementTransformation1x2(int elnr,
                                           const double *xi,
                                           double *x,
                                           double *dxdxi) const {};

void Ngx_MyMesh ::ElementTransformation1x1(int elnr,
                                           const double *xi,
                                           double *x,
                                           double *dxdxi) const {};

void Ngx_MyMesh ::ElementTransformation0x2(int elnr,
                                           const double *xi,
                                           double *x,
                                           double *dxdxi) const {};

void Ngx_MyMesh ::ElementTransformation0x1(int elnr,
                                           const double *xi,
                                           double *x,
                                           double *dxdxi) const {};

void Ngx_MyMesh ::MultiElementTransformation3x3(int elnr, int npts,
                                                const double *xi, size_t sxi,
                                                double *x, size_t sx,
                                                double *dxdxi, size_t sdxdxi) const {};

void Ngx_MyMesh ::MultiElementTransformation2x2(int elnr, int npts,
                                                const double *xi, size_t sxi,
                                                double *x, size_t sx,
                                                double *dxdxi, size_t sdxdxi) const {};

void Ngx_MyMesh ::MultiElementTransformation2x3(int elnr, int npts,
                                                const double *xi, size_t sxi,
                                                double *x, size_t sx,
                                                double *dxdxi, size_t sdxdxi) const {};

void Ngx_MyMesh ::MultiElementTransformation1x3(int elnr, int npts,
                                                const double *xi, size_t sxi,
                                                double *x, size_t sx,
                                                double *dxdxi, size_t sdxdxi) const {};

void Ngx_MyMesh ::MultiElementTransformation0x3(int elnr, int npts,
                                                const double *xi, size_t sxi,
                                                double *x, size_t sx,
                                                double *dxdxi, size_t sdxdxi) const {};

void Ngx_MyMesh ::MultiElementTransformation1x2(int elnr, int npts,
                                                const double *xi, size_t sxi,
                                                double *x, size_t sx,
                                                double *dxdxi, size_t sdxdxi) const {};

void Ngx_MyMesh ::MultiElementTransformation1x1(int elnr, int npts,
                                                const double *xi, size_t sxi,
                                                double *x, size_t sx,
                                                double *dxdxi, size_t sdxdxi) const {};

void Ngx_MyMesh ::MultiElementTransformation0x2(int elnr, int npts,
                                                const double *xi, size_t sxi,
                                                double *x, size_t sx,
                                                double *dxdxi, size_t sdxdxi) const {};

void Ngx_MyMesh ::MultiElementTransformation0x1(int elnr, int npts,
                                                const double *xi, size_t sxi,
                                                double *x, size_t sx,
                                                double *dxdxi, size_t sdxdxi) const {};

void Ngx_MyMesh ::MultiElementTransformation3x3(int elnr, int npts,
                                                const tAVXd *xi, size_t sxi,
                                                tAVXd *x, size_t sx,
                                                tAVXd *dxdxi, size_t sdxdxi) const {};

void Ngx_MyMesh ::MultiElementTransformation2x2(int elnr, int npts,
                                                const tAVXd *xi, size_t sxi,
                                                tAVXd *x, size_t sx,
                                                tAVXd *dxdxi, size_t sdxdxi) const {};

void Ngx_MyMesh ::MultiElementTransformation2x3(int elnr, int npts,
                                                const tAVXd *xi, size_t sxi,
                                                tAVXd *x, size_t sx,
                                                tAVXd *dxdxi, size_t sdxdxi) const {};

void Ngx_MyMesh ::MultiElementTransformation1x3(int elnr, int npts,
                                                const tAVXd *xi, size_t sxi,
                                                tAVXd *x, size_t sx,
                                                tAVXd *dxdxi, size_t sdxdxi) const {};

void Ngx_MyMesh ::MultiElementTransformation0x3(int elnr, int npts,
                                                const tAVXd *xi, size_t sxi,
                                                tAVXd *x, size_t sx,
                                                tAVXd *dxdxi, size_t sdxdxi) const {};

void Ngx_MyMesh ::MultiElementTransformation1x2(int elnr, int npts,
                                                const tAVXd *xi, size_t sxi,
                                                tAVXd *x, size_t sx,
                                                tAVXd *dxdxi, size_t sdxdxi) const {};

void Ngx_MyMesh ::MultiElementTransformation1x1(int elnr, int npts,
                                                const tAVXd *xi, size_t sxi,
                                                tAVXd *x, size_t sx,
                                                tAVXd *dxdxi, size_t sdxdxi) const {};

void Ngx_MyMesh ::MultiElementTransformation0x2(int elnr, int npts,
                                                const tAVXd *xi, size_t sxi,
                                                tAVXd *x, size_t sx,
                                                tAVXd *dxdxi, size_t sdxdxi) const {};

void Ngx_MyMesh ::MultiElementTransformation0x1(int elnr, int npts,
                                                const tAVXd *xi, size_t sxi,
                                                tAVXd *x, size_t sx,
                                                tAVXd *dxdxi, size_t sdxdxi) const {};

NG_INLINE DLL_HEADER const Ng_Node<0> Ngx_MyMesh ::GetNode0(int nr) const 
{
    Ng_Node<0> n;

    n.elements.ne = mesh->getNodes()[nr].partOfElement.size();
    n.elements.ptr = &(mesh->getNodes()[nr].partOfElement[0]);

    n.bnd_elements.ne = mesh->getNodes()[nr].partOfBndElement.size();
    n.bnd_elements.ptr = &mesh->getNodes()[nr].partOfBndElement[0];

    return n;
};

NG_INLINE DLL_HEADER const Ng_Node<1> Ngx_MyMesh ::GetNode1(int nr) const 
{
    Ng_Node<1> n;

    n.vertices.ptr = &mesh->getEdges()[nr].nodeIdx[0];

    return n;
};

NG_INLINE DLL_HEADER const Ng_Node<2> Ngx_MyMesh ::GetNode2(int nr) const 
{
    Ng_Node<2> n;

    n.vertices.nv = mesh->getFaces()[nr].nodeIdx.size();
    n.vertices.ptr = &mesh->getFaces()[nr].nodeIdx[0];

    n.edges.ned = mesh->getFaces()[nr].edgeIdx.size();
    n.edges.ptr = &mesh->getFaces()[nr].edgeIdx[0];

    n.surface_el = &mesh->getFaces()[nr].boundary ? 1 : -1;

    return n;
};

int Ngx_MyMesh ::GetNNodes1() { return mesh->getNumNodes(); }
int Ngx_MyMesh ::GetNNodes2() { return mesh->getNumEdges(); }

void Ngx_MyMesh ::GetParentNodes(int ni, int *parents) const {};
int Ngx_MyMesh ::GetParentElement(int ei) const { return 0; };
int Ngx_MyMesh ::GetParentSElement(int ei) const { return 0; };

int Ngx_MyMesh ::GetNIdentifications() const { return 3; };
int Ngx_MyMesh ::GetIdentificationType(int idnr) const { return 3; };
Ng_Buffer<int[2]> Ngx_MyMesh ::GetPeriodicVertices(int idnr) const {};

inline int Ngx_MyMesh ::GetTimeStamp() const { return 0; };
}