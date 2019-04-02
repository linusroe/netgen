from ngsolve import *
from netgen.mymesh import *

# Walk through all elements of mesh
output = False

# Create 2 x 2 x 2 Mesh
mesh = MyMesh(2,2,2)
ngxmymesh = Ngx_MyMesh(mesh)
ngsmesh = Mesh(ngxmymesh)

# Iterate and print all elements
if output:
    for v in ngsmesh.vertices:
        print (v, v.point)

    input("points done")

    for e in ngsmesh.edges:
        print (e, e.elements)

    input("edges done")

    for el in ngsmesh.Elements(VOL):
        print (el, el.vertices, el.edges)

    input("vertices done")

    for el in ngsmesh.Elements(BND):
        print (el, el.vertices, el.edges)

    input("volumes done")

    print("Mesh works up to H1")

V = H1(ngsmesh,order=1,no_low_order_space=True)
gfu = GridFunction(V)

# Compute various integrals to verify mesh function
gfu.Set(1) # == 1
integral = Integrate(gfu, ngsmesh)
print("Int 1 dxdydz: ", integral, " == ", 1)

gfu.Set(x+y+z) # == 1.5
integral = Integrate(gfu, ngsmesh)
print("Int x+y+z dxdydz: ", integral, " == ", 1.5)

gfu.Set(x*sin(y**2)+z) # == .655
integral = Integrate(gfu, ngsmesh)
print("Int x*sin(y^2)+z dxdydz: ", integral, " == ", .655)


# 2 Dimensional example
mesh2 = MyMesh(2,2, 0)
ngxmymesh2 = Ngx_MyMesh(mesh2)
ngsmesh2 = Mesh(ngxmymesh2)

V2 = H1(ngsmesh2,order=1,no_low_order_space=True)
gfu = GridFunction(V)

gfu.Set(x*sin(y**2)) # == .155
integral = Integrate(gfu, ngsmesh)
print("Int x*sin(y^2) dxdy: ", integral, " == ", .155)