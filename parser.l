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
%{

#include "parser.tab.h"

extern unsigned int line;

%}

%%

"v"       { return VERT; }
"vn"      { return NORMAL; }
"vt"      { return TEXTURE; }
"o"       { return OBJECT; }
"s"       { return SMOOTH; }
"f"       { return FACE; }
"l"       { return ELL; }
"mtllib"  { return MTLLIB; }
"usemtl"  { return USEMTL; }
"/"       { return SLASH; }

[-]{0,1}[0-9.]+      { yylval.number = atof(yytext); return NUMBER; }
[A-Za-z0-9\._\-()]+  { yylval.string = yytext; return STRING; }
#+.*\n               { line++; /*Comment*/ }
\n                   { line++; return EOL; }
[ \t\r\f\v]          { }
.                    { printf("Unknown: %s\n",yytext); }

%%
