%{
#include <stdio.h>
#include "func.h"
#include "linkedlist.h"
#include "object.h"
#include "verticeList.h"

unsigned int line = 0;
unsigned int v_num = 0;
int yylex();
extern char *yytext;
void yyerror(char *s);

linkedList * objectList;
linkedList * vertices;
linkedListNode * objectListNode;
linkedListNode * verticesListNode;

vertice tempVertice;

%}

%union {
  double number;
  char * string;
}

%token VERT
%token NORMAL
%token TEXTURE
%token OBJECT
%token SETTING
%token FACE
%token MTLLIB
%token USEMTL
%token ELL
%token EOL
%token SLASH
%token <number> NUMBER
%token <string> STRING

%%

list: 
| list line EOL
;

line:
 MTLLIB STRING { printf("/* Load Material library: %s */\n", $2); }
| USEMTL STRING { /*printf("Use Material: %s\n",$2);*/ }
| OBJECT STRING {
  printf("/* New object: %s */\n", $2);
  objectListNode = addNewNode(objectList);
 }
| VERT NUMBER NUMBER NUMBER { 
  printf("#%u ",++v_num); printf("Vertex: %f %f %f\n",$2,$3,$4);

  tempVertice.x = $2;
  tempVertice.y = $3;
  tempVertice.z = $4;

  if(objectListNode!=0) {
    vertices = getVerticeList(objectListNode);
    if(vertices!=0) {
      verticesListNode = addNewNode(vertices);
      storeVerticeData(verticesListNode, tempVertice);
    } else yyerror("Error: Cannot store vertice data\n");
  } else yyerror("Error: No object was defined\n");

 }
| FACE numberlist { printf("face\n"); /*printf("Face(4) %f %f %f\n",$2,$3,$4);*/ }
| ELL NUMBER NUMBER { /**/ }
| TEXTURE NUMBER NUMBER {   }
| SETTING STRING { /*printf("Setting: %s\n",$2);*/ }
| SETTING NUMBER { /*printf("Setting: %s\n",$2);*/ }
;

numberlist: 
| numberlist NUMBER { printf("%u ", (unsigned int)$2); }
| numberlist NUMBER SLASH { printf("%u ", (unsigned int)$2); }
;

%%

int main(int argc, char **argv)
{  
  objectList = createNewObjectList();

  if(parseParams(argc, argv))
    {
      return 0;
    }
  yyparse();

  printf("List: %u objects\n",getNumNodes(objectList));
  freeList(objectList);

  return 0;
}

void yyerror(char *s)
{
  printf("error: %s at line %u\n", s, line);
}
