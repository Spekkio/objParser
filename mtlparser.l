/*
    objParser: converting Wavefront .obj format into OpenGL c-code
    Copyright (C) 2015  Daniel Hedeblom

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

/** 
 * @todo read http://paulbourke.net/dataformats/mtl/
 */

%{
#include "mtlparser.tab.h"

unsigned int line;

%}

%%

"newmtl" { return NEWMTL; }
"Ka"     { return AMBIENT; }
"Kd"     { return DIFFUSE; }
"Ks"     { return SPECULAR; }
"Ns"     { return SPECULAR_EXPONENT; }
"Ni"     { return OPTICAL_DENSITY; }
"d"      { return DISSOLVE; /*transparency*/ }
"illum"  { return ILLUM; }
"map_Kd" { return TEXTURE_DIFFUSE; }
"map_Ka" { return TEXTURE_AMBIENT; }
"map_Ks" { return TEXTURE_SPECULAR; }

[-]{0,1}[0-9.]+      { yylval.number = atof(yytext); return NUMBER; }
[A-Za-z0-9\._\-()/]+ { yylval.string = yytext; return STRING; }
#+.*\n               { line++; /*Comment*/ }
\n                   { line++; return EOL; }
[ \t\r\f\v]          { }
.                    { printf("Unknown: %s\n",yytext); }

%%

/*
illum options

0. Color on and Ambient off
1. Color on and Ambient on
2. Highlight on
3. Reflection on and Ray trace on
4. Transparency: Glass on, Reflection: Ray trace on
5. Reflection: Fresnel on and Ray trace on
6. Transparency: Refraction on, Reflection: Fresnel off and Ray trace on
7. Transparency: Refraction on, Reflection: Fresnel on and Ray trace on
8. Reflection on and Ray trace off
9. Transparency: Glass on, Reflection: Ray trace off
10. Casts shadows onto invisible surfaces
*/
