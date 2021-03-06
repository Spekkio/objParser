# objParser

Convert a Blender object (Wavefront .obj file) into c code. Currently the program reads from stdin and prints to stdout like this

    ./parser -stdout < cube.obj > cube.code

Display object in a window (Using SDL), control using W,A,S,D and Q,E for up and down movement. Hold left mouse button down to look around.

    ./parser -gui < cube.obj

## Millennium Falcon example

Millennium Falcon model rendered in Blender
![Millennium Falcon](http://vps.spekkio.se/bilder/falcon_render.jpg "Millennium Falcon Rendered in Blender")

This is loaded into objParser with the -gui parameter, currently no textures or colors.

     bzip2 -dc Falcon_BlendSwap.obj.bz2 | ./parser -gui

![Millennium Falcon OpenGL](http://vps.spekkio.se/bilder/falcon.gif "Millennium Falcon implemented in OpenGL c code")

<a href="https://www.youtube.com/watch?v=9wKkcZERKmM">Youtube Video</a>

Millennium Falcon model by KuhnIndustries
<a href="http://www.blendswap.com/blends/view/48469">http://www.blendswap.com/blends/view/48469</a>

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

    ./parser -stdout < cube.obj

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

* Handle Textures, Colors, Normals, .mtl files, etc.
* Scriptable outputs using LUA, to support VBO output and whatever.

### BUGS

1. The character '/' Forward slash can be used in strings, not supported by the parser. Probably more characters can be used.

2. in parser.y, facenumberlist NUMBER SLASH NUMBER doesn't use the second number.
For example a face definition like this is not handled.

    f 2616/5 711/11 712/12 713/13 714/14 715/15 716/16 717/17 718/18 719/19 720/20 721/21 722/22 723/23 724/24 725/25 726/26 727/27 728/28 729/29 730/30 731/31 732/32 733/33 734/34 735/35 736/36 737/37 2618/38
