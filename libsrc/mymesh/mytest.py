#import netgen.gui
from ngsolve import *
from netgen.csg import unit_cube
from ngsolve.meshes import *

mesh = MakeQuadMesh(nx=5,ny=5)
#asdf

for v in mesh.vertices:
    print (v, v.point)

# input("step 1 done")

for e in mesh.edges:
    print (e)# e.elements)

# input("step 2 done")

# for el in mesh.Elements(VOL):
#     print (el, el.vertices, el.edges)

# input("step 3 done")

# for el in mesh.Elements(BND):
#     print (el, el.vertices, el.edges)

# input("step 4 done")


# V=H1(mesh,order=1)
# gfu = GridFunction(V)
# gfu.Set(sin(10*x))
# integral = Integrate(gfu,mesh)

# Draw(gfu,mesh,"u")
# print(integral, " =!= ", 0.183129283601153)


from netgen.mymesh import *

mesh = MyMesh(2,2,2)
ngxmymesh = Ngx_MyMesh(mesh)

from ngsolve import *
ngsmesh = Mesh(ngxmymesh)

for v in ngsmesh.vertices:
    print (v, v.point)

input("step 1 done")

for e in ngsmesh.edges:
    print (e, e.elements)

# input("step 2 done")

# for el in mesh.Elements(VOL):
#     print (el, el.vertices, el.edges)

# input("step 3 done")

# for el in mesh.Elements(BND):
#     print (el, el.vertices, el.edges)

# input("step 4 done")

print("Mesh works up to H1")

V=H1(ngsmesh,order=1)
gfu = GridFunction(V)
gfu.Set(sin(10*x))
integral = Integrate(gfu,mesh)

# Draw(gfu,mesh,"u")
print(integral, " =!= ", 0.183129283601153)
