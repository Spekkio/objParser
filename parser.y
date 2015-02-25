%{
#include <stdio.h>
#include "func.h"

unsigned int line = 0;
int yylex();
extern char *yytext;

%}

%union {
  double number;
  char * string;
}

%token VERT
%token NORMAL
%token OBJECT
%token SETTING
%token FACE
%token MTLLIB
%token USEMTL
%token EOL
%token <number> NUMBER
%token <string> STRING

%%

list: 
| list line EOL
| list EOL
;

line:
 MTLLIB STRING { printf("/* Load Material library: %s */\n", $2); }
| USEMTL STRING { /*printf("Use Material: %s\n",$2);*/ }
| OBJECT STRING { printf("/* New object: %s */\n glBegin(GL_QUADS);\n", $2); }
| VERT NUMBER NUMBER NUMBER { printglVertex3f($2,$3,$4); }
| FACE NUMBER NUMBER NUMBER { /*printf("Face(4) %f %f %f\n",$2,$3,$4);*/ }
| FACE NUMBER NUMBER NUMBER NUMBER { /*printf("Face(3) %f %f %f %f\n",$2,$3,$4,$5);*/ }
| SETTING STRING { /*printf("Setting: %s\n",$2);*/ }
;

%%

main(int argc, char **argv)
{  
  if(parseParams(argc, argv))
    {
      return 0;
    }
  yyparse();
}

yyerror(char *s)
{
  printf("error: %s at line %u\n", s, line);
}
