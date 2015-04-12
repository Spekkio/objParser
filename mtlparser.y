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
#include <stdio.h>
  int yylex (void);
  extern char *yytext;
  void yyerror(char *s);

  extern unsigned int line;
%}

%union {
  double number;
  char * string;
}

%token NEWMTL
%token AMBIENT
%token DIFFUSE
%token SPECULAR
%token SPECULAR_EXPONENT
%token OPTICAL_DENSITY
%token DISSOLVE
%token ILLUM
%token TEXTURE_DIFFUSE
%token TEXTURE_AMBIENT
%token TEXTURE_SPECULAR
%token <number> NUMBER
%token <string> STRING
%token EOL

%%

list:
| list line EOL
;

line:
| NEWMTL STRING { printf("New Material: %s\n",$2); }
| AMBIENT NUMBER NUMBER NUMBER { printf("Ka %f %f %f #Shadow Color\n", $2,$3,$4);  }
| DIFFUSE NUMBER NUMBER NUMBER { printf("Kd %f %f %f #Main Color\n", $2,$3,$4);  }
| SPECULAR NUMBER NUMBER NUMBER { printf("Ks %f %f %f #Light Color\n", $2,$3,$4);  }
| SPECULAR_EXPONENT NUMBER { printf("Ns %f\n", $2);  }
| OPTICAL_DENSITY NUMBER { printf("Ni %f\n", $2); }
| DISSOLVE NUMBER { printf("d %f\n", $2); }
| ILLUM NUMBER { printf("illum %f\n", $2); }
| TEXTURE_DIFFUSE STRING { printf("map_Kd: %s\n",$2); }
| TEXTURE_AMBIENT STRING { printf("map_Ka: %s\n",$2); }
| TEXTURE_SPECULAR STRING { printf("map_Ks: %s\n",$2);}
;

%%

int main(int argc __attribute__((__unused__)), char **argv __attribute__((__unused__)))
{
  yyparse();
}

void yyerror(char *s)
{
  fprintf(stderr, "error: %s at line %u\n", s, line);
}
