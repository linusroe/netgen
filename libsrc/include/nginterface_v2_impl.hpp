NGX_INLINE DLL_HEADER Ng_Point Ngx_netgen_Mesh :: GetPoint (int nr) const
{
  return Ng_Point (&mesh->Point(PointIndex(nr+PointIndex::BASE))(0));
}


NGX_INLINE DLL_HEADER int Ngx_netgen_Mesh :: GetElementIndex0 (size_t nr) const
{
  return (*mesh).pointelements[nr].index;
}

NGX_INLINE DLL_HEADER int Ngx_netgen_Mesh :: GetElementIndex1 (size_t nr) const
{
  /*
  if(mesh->GetDimension()==3)
    return (*mesh)[SegmentIndex(nr)].edgenr;
  else
    return (*mesh)[SegmentIndex(nr)].si;
  */
  if(mesh->GetDimension()==3)
    return mesh->LineSegments()[nr].edgenr;
  else
    return mesh->LineSegments()[nr].si;    
}
  
NGX_INLINE DLL_HEADER int Ngx_netgen_Mesh :: GetElementIndex2 (size_t nr) const
{
  int ind = (*mesh)[SurfaceElementIndex(nr)].GetIndex(); 
  return mesh->GetFaceDescriptor(ind).BCProperty();
}

NGX_INLINE DLL_HEADER int Ngx_netgen_Mesh :: GetElementIndex3 (size_t nr) const
{
  return (*mesh)[ElementIndex(nr)].GetIndex();
}


NGX_INLINE DLL_HEADER Ng_Element Ngx_netgen_Mesh :: GetElement0 (size_t nr) const
{
  const Element0d & el = mesh->pointelements[nr];
  
  Ng_Element ret;
  ret.type = NG_PNT;
  ret.index = el.index;
  
  ret.points.num = 1;
  ret.points.ptr = (int*)&el.pnum;
  
  ret.vertices.num = 1;
  ret.vertices.ptr = (int*)&el.pnum;
  
  ret.edges.num = 0;
  ret.edges.ptr = NULL;
  
  ret.faces.num = 0;
  ret.faces.ptr = NULL;

  ret.facets.num = 1;
  ret.facets.base = 1;
  ret.facets.ptr = (int*)&el.pnum;
  
  return ret;
}



NGX_INLINE DLL_HEADER Ng_Element Ngx_netgen_Mesh :: GetElement1 (size_t nr) const
{
  // const Segment & el = mesh->LineSegment (SegmentIndex(nr));
  const Segment & el = mesh->LineSegments()[nr];

  Ng_Element ret;
  ret.type = NG_ELEMENT_TYPE(el.GetType());
  if(mesh->GetDimension()==3)
    ret.index = el.edgenr;
  else
    ret.index = el.si;
  if (mesh->GetDimension() == 2)
    ret.mat = mesh->GetBCNamePtr(el.si-1);
  else
    {
      if (mesh->GetDimension() == 3)
        ret.mat = mesh->GetCD2NamePtr(el.edgenr-1);
      else
        ret.mat = mesh->GetMaterialPtr(el.si);
    }

  ret.points.num = el.GetNP();
  ret.points.ptr = (int*)&(el[0]);

  ret.vertices.num = 2;
  ret.vertices.ptr = (int*)&(el[0]);

  ret.edges.num = 1;
  ret.edges.ptr = (T_EDGE2*)mesh->GetTopology().GetSegmentElementEdgesPtr (nr);

  ret.faces.num = 0;
  ret.faces.ptr = NULL;

  if (mesh->GetDimension() == 2)
    {
      ret.facets.num = 1;
      ret.facets.base = 0;
      ret.facets.ptr = (int*)ret.edges.ptr;
    }
  else
    {
      ret.facets.num = 2;
      ret.facets.base = 1;
      ret.facets.ptr = (int*)&(el[0]);
    }

  // ret.is_curved = mesh->GetCurvedElements().IsSegmentCurved(nr);
  ret.is_curved = el.IsCurved();

  return ret;
}

NGX_INLINE DLL_HEADER Ng_Element Ngx_netgen_Mesh :: GetElement2 (size_t nr) const
{
  // const Element2d & el = mesh->SurfaceElement (SurfaceElementIndex (nr));
  const Element2d & el = mesh->SurfaceElements()[nr];
  
  Ng_Element ret;
  ret.type = NG_ELEMENT_TYPE(el.GetType());
  const FaceDescriptor & fd = mesh->GetFaceDescriptor(el.GetIndex());
  ret.index = fd.BCProperty();
  if (mesh->GetDimension() == 3)
    ret.mat = &fd.GetBCName();
  else
    ret.mat = mesh -> GetMaterialPtr(ret.index);
  ret.points.num = el.GetNP();
  ret.points.ptr  = (int*)&el[0];

  ret.vertices.num = el.GetNV();
  ret.vertices.ptr = (int*)&(el[0]);

  ret.edges.num = MeshTopology::GetNEdges (el.GetType());
  ret.edges.ptr = (T_EDGE2*)mesh->GetTopology().GetSurfaceElementEdgesPtr (nr);

  ret.faces.num = MeshTopology::GetNFaces (el.GetType());
  ret.faces.ptr = (T_FACE2*)mesh->GetTopology().GetSurfaceElementFacesPtr (nr);

  if (mesh->GetDimension() == 3)
    {
      ret.facets.num = ret.faces.num;
      ret.facets.base = 0;
      ret.facets.ptr = (int*)ret.faces.ptr;
    }
  else
    {
      ret.facets.num = ret.edges.num;
      ret.facets.base = 0;      
      ret.facets.ptr = (int*)ret.edges.ptr;
    }
  ret.is_curved = el.IsCurved();
  return ret;
}

NGX_INLINE DLL_HEADER Ng_Element Ngx_netgen_Mesh :: GetElement3 (size_t nr) const
{
  // const Element & el = mesh->VolumeElement (ElementIndex (nr));
  const Element & el = mesh->VolumeElements()[nr];
  
  Ng_Element ret;
  ret.type = NG_ELEMENT_TYPE(el.GetType());
  ret.index = el.GetIndex();
  ret.mat = mesh -> GetMaterialPtr(ret.index);
  ret.points.num = el.GetNP();
  ret.points.ptr = (int*)&el[0];

  ret.vertices.num = el.GetNV();
  ret.vertices.ptr = (int*)&(el[0]);

  ret.edges.num = MeshTopology::GetNEdges (el.GetType());
  ret.edges.ptr = (T_EDGE2*)mesh->GetTopology().GetElementEdgesPtr (nr);

  ret.faces.num = MeshTopology::GetNFaces (el.GetType());
  ret.faces.ptr = (T_FACE2*)mesh->GetTopology().GetElementFacesPtr (nr);

  ret.facets.num = ret.faces.num;
  ret.facets.base = 0;
  ret.facets.ptr = (int*)ret.faces.ptr;

  ret.is_curved = el.IsCurved();
  return ret;
}



NGX_INLINE DLL_HEADER
const string &  Ngx_netgen_Mesh :: GetMaterialCD0 (int region_nr) const
{
  return mesh->GetMaterial(region_nr+1);
}

NGX_INLINE DLL_HEADER
const string &  Ngx_netgen_Mesh :: GetMaterialCD1 (int region_nr) const
{
  return mesh->GetBCName(region_nr);
}

NGX_INLINE DLL_HEADER
const string &  Ngx_netgen_Mesh :: GetMaterialCD2 (int region_nr) const
{
  return mesh->GetCD2Name(region_nr);
}

NGX_INLINE DLL_HEADER
const string &  Ngx_netgen_Mesh :: GetMaterialCD3 (int region_nr) const
{
  return mesh->GetCD3Name(region_nr);
}





NGX_INLINE DLL_HEADER int Ngx_netgen_Mesh :: GetNNodes<1> ()
{
  return mesh->GetTopology().GetNEdges();
}

NGX_INLINE DLL_HEADER int Ngx_netgen_Mesh :: GetNNodes<2> ()
{
  return mesh->GetTopology().GetNFaces();
}

NGX_INLINE DLL_HEADER const Ng_Node<0> Ngx_netgen_Mesh :: GetNode<0> (int vnr) const
{
  Ng_Node<0> node;
  vnr++;
  switch (mesh->GetDimension())
    {
    case 3:
      {
        FlatArray<ElementIndex> ia = mesh->GetTopology().GetVertexElements(vnr);
        node.elements.ne = ia.Size();
        node.elements.ptr = (int*)&ia[0];
        
        FlatArray<SurfaceElementIndex> bia = mesh->GetTopology().GetVertexSurfaceElements(vnr);
        node.bnd_elements.ne = bia.Size();
        node.bnd_elements.ptr = (int*)&bia[0];
        break;
      }
    case 2:
      {
        FlatArray<SurfaceElementIndex> ia = mesh->GetTopology().GetVertexSurfaceElements(vnr);
        node.elements.ne = ia.Size();
        node.elements.ptr = (int*)&ia[0];
        
        FlatArray<SegmentIndex> bia = mesh->GetTopology().GetVertexSegments(vnr);
        node.bnd_elements.ne = bia.Size();
        node.bnd_elements.ptr = (int*)&bia[0];
        break;
      }
    case 1:
      {
        FlatArray<SegmentIndex> ia = mesh->GetTopology().GetVertexSegments(vnr);
        node.elements.ne = ia.Size();
        node.elements.ptr = (int*)&ia[0];
        
        FlatArray<int> bia = mesh->GetTopology().GetVertexPointElements(vnr);
        node.bnd_elements.ne = bia.Size();
        node.bnd_elements.ptr = (int*)&bia[0];
        break;
      }
    default:
      ;
    }
  return node;
}
  
NGX_INLINE DLL_HEADER const Ng_Node<1> Ngx_netgen_Mesh :: GetNode<1> (int nr) const
{
  Ng_Node<1> node;
  node.vertices.ptr = mesh->GetTopology().GetEdgeVerticesPtr(nr);
  return node;
}

NGX_INLINE DLL_HEADER const Ng_Node<2> Ngx_netgen_Mesh :: GetNode<2> (int nr) const
{
  Ng_Node<2> node;
  node.vertices.ptr = mesh->GetTopology().GetFaceVerticesPtr(nr);
  node.vertices.nv = (node.vertices.ptr[3] == 0) ? 3 : 4;
  node.surface_el = mesh->GetTopology().GetFace2SurfaceElement (nr+1)-1;
  return node;
}


NGX_INLINE DLL_HEADER Ng_Buffer<int[2]> Ngx_netgen_Mesh :: GetPeriodicVertices(int idnr) const
{
  Array<INDEX_2> apairs;
  mesh->GetIdentifications().GetPairs (idnr+1, apairs);
  for(auto& ind : apairs)
    {
      ind.I1()--;
      ind.I2()--;
    }
  typedef int ti2[2];
  return { apairs.Size(), (ti2*)(void*)apairs.Release() };
}


NGX_INLINE void Ngx_netgen_Mesh :: GetParentNodes (int ni, int * parents) const
{
  ni++;
  if (ni <= mesh->mlbetweennodes.Size())
    {
      parents[0] = mesh->mlbetweennodes.Get(ni).I1()-1;
      parents[1] = mesh->mlbetweennodes.Get(ni).I2()-1;
      }
  else
    parents[0] = parents[1] = -1;
}



inline auto Ngx_netgen_Mesh :: GetTimeStamp() const { return mesh->GetTimeStamp(); }
