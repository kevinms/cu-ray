
---

**camera**
  * camera name
  * pixeldim
  * worlddim
  * viewpoint

**material**
  * material name
  * diffuse
  * ambient
  * specular

---

_Scene Example_
```
camera cam1
{
  pixeldim  640 480
  worlddim  8 6
  viewpoint 4 3 6
}
material blue
{
   specular 0 1 0
   diffuse 0  5 0
}
material orange
{
   ambient 5 4 0.1
   diffuse 5 4  0
}
```