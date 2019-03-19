from ngsolve import *
from netgen.mymesh import *

output = 0

mesh = MyMesh(2,2,2)
ngxmymesh = Ngx_MyMesh(mesh)
ngsmesh = Mesh(ngxmymesh)

if output:
    for v in ngsmesh.vertices:
        print (v, v.point)

    input("step 1 done")

    for e in ngsmesh.edges:
        print (e, e.elements)

    input("step 2 done")

    for el in ngsmesh.Elements(VOL):
        print (el, el.vertices, el.edges)

    input("step 3 done")

    for el in ngsmesh.Elements(BND):
        print (el, el.vertices, el.edges)

    input("step 4 done")

    print("Mesh works up to H1")

V=H1(ngsmesh,order=1,no_low_order_space=True)
gfu = GridFunction(V)

gfu.Set(1) # == 1
integral = Integrate(gfu, ngsmesh)
print("Int 1 dxdydz: ", integral, " =!= ", 1)

gfu.Set(x+y+z) # == 1.5
integral = Integrate(gfu, ngsmesh)
print("Int x+y+z dxdydz: ", integral, " =!= ", 1.5)

gfu.Set(x*sin(y**2)+z) # == .655
integral = Integrate(gfu, ngsmesh)
print("Int x*sin(y^2)+z dxdydz: ", integral, " =!= ", .665)
# Draw(gfu,mesh,"u")
