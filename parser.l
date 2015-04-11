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
 * @todo go through this, http://www.martinreddy.net/gfx/3d/OBJ.spec
 */

%{

#include "parser.tab.h"

extern unsigned int line;

%}

%%

"v"          { return VERT; }
"vn"         { return NORMAL; /* TODO*/ }
"vt"         { return TEXTURE; /*TODO*/ }
"vp"         { return V_PARAMETER; /*TODO*/ }
"cstype"     { return CS_CURVE; /*TODO*/ }
"deg"        { return DEGREE; /*TODO*/ }
"bmat"       { return BASIS_MATRIX; /*TODO*/ }
"step"       { return STEP_SIZE; /*TODO*/ }
"o"          { return OBJECT; }
"p"          { return POINT; /*Specifies a point element and its vertex.*/ /*TODO*/ }
"f"          { return FACE; /*Specifies a face element and its vertex reference number.*/ }
"l"          { return LINE; /*Specifies a line and its vertex reference numbers.*/ /*TODO*/ }
"curv"       { return CURVE; /*TODO*/ }
"curv2"      { return CURVE2; /*TODO*/ }
"surf"       { return SURFACE; /*TODO*/ }
"parm"       { return PARAMETER; /*TODO*/ }
"trim"       { return TRIM; /*TODO*/ }
"hole"       { return HOLE; /*TODO*/ }
"scrv"       { return S_CURVE; /*TODO*/ }
"sp"         { return S_POINT; /*TODO*/ }
"end"        { return END; /*TODO*/ }
"con"        { return CONNECT; /*TODO*/ }
"g"          { return GROUP; /*TODO*/ }
"s"          { return SMOOTH; /*TODO*/ }
"mg"         { return MERGE; /*TODO*/ }
"bevel"      { return BEVEL; /*TODO*/ }
"c_interp"   { return COLOR_INTERP; /*TODO*/ }
"d_interp"   { return DISSOLVE_INTERP; /*TODO*/ }
"lod"        { return L_DETAIL; /*TODO*/ }
"mtllib"     { return MTLLIB; /*TODO*/ }
"usemtl"     { return USEMTL; /*TODO*/ }
"shadow_obj" { return SHADOW_CAST; /*TODO*/ }
"trace_obj"  { return RAY_TRACE; /*TODO*/ }
"ctech"      { return CURVE_APPROX; /*TODO*/ }
"stech"      { return SURFACE_APPROX; /*TODO*/ }
"/"          { return SLASH; }

[-]{0,1}[0-9.]+      { yylval.number = atof(yytext); return NUMBER; }
[A-Za-z0-9\._\-()]+  { yylval.string = yytext; return STRING; }
#+.*\n               { line++; /*Comment*/ }
\n                   { line++; return EOL; }
[ \t\r\f\v]          { }
.                    { fprintf(stderr,"Unknown: %s\n",yytext); }

%%
/*
"/"          { return SLASH; }
*/
