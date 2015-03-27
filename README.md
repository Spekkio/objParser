# objParser

Export a Blender scene into a Wavefront .obj file

For example, make a simple cube in Blender and export it to cube.obj

    # Blender v2.69 (sub 0) OBJ File: ''
    # www.blender.org
    mtllib cube.mtl
    o Cube
    v 1.000000 -1.000000 -1.000000
    v 1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 -1.000000
    v 1.000000 1.000000 -0.999999
    v 0.999999 1.000000 1.000001
    v -1.000000 1.000000 1.000000
    v -1.000000 1.000000 -1.000000
    usemtl Material
    s off
    f 1 2 3 4
    f 5 8 7 6
    f 1 5 6 2
    f 2 6 7 3
    f 3 7 8 4
    f 5 1 4 8

Convert it into c-code

	./parser < cube.obj

The output will look like this

```javascript
glBegin(GL_QUADS);
glVertex3f(1.000000,-1.000000,-1.000000);
glVertex3f(1.000000,-1.000000,1.000000);
glVertex3f(-1.000000,-1.000000,1.000000);
glVertex3f(-1.000000,-1.000000,-1.000000);
glVertex3f(1.000000,1.000000,-0.999999);
glVertex3f(-1.000000,1.000000,-1.000000);
glVertex3f(-1.000000,1.000000,1.000000);
glVertex3f(0.999999,1.000000,1.000001);
glVertex3f(1.000000,-1.000000,-1.000000);
glVertex3f(1.000000,1.000000,-0.999999);
glVertex3f(0.999999,1.000000,1.000001);
glVertex3f(1.000000,-1.000000,1.000000);
glVertex3f(1.000000,-1.000000,1.000000);
glVertex3f(0.999999,1.000000,1.000001);
glVertex3f(-1.000000,1.000000,1.000000);
glVertex3f(-1.000000,-1.000000,1.000000);
glVertex3f(-1.000000,-1.000000,1.000000);
glVertex3f(-1.000000,1.000000,1.000000);
glVertex3f(-1.000000,1.000000,-1.000000);
glVertex3f(-1.000000,-1.000000,-1.000000);
glVertex3f(1.000000,1.000000,-0.999999);
glVertex3f(1.000000,-1.000000,-1.000000);
glVertex3f(-1.000000,-1.000000,-1.000000);
glVertex3f(-1.000000,1.000000,-1.000000);
glEnd();
```
