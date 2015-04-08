# objParser

Convert a Blender object (Wavefront .obj file) into c code. Currently the program reads from stdin and prints to stdout like this

    ./parser < cube.obj > cube.code

## Spaceship example

![Spaceship](http://vps.spekkio.se/bilder/ship.png "Spaceship Rendered in Blender")

This was exported to c code and implemented into a program (I used [sdltest](https://github.com/Spekkio/sdltest)), currently no textures or colors.

![Spaceship OpenGL](http://vps.spekkio.se/bilder/spaceship.gif "Spaceship implemented in OpenGL c code")
<a href="https://www.youtube.com/watch?v=GpCKgM7oZ1s">Youtube Video</a>

## Simple cube example

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

## TODO

Handle Textures, Colors, etc.

Scriptable outputs using LUA, to support VBO output and whatever.