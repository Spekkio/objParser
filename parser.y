%{
#include <stdio.h>
#include "func.h"
#include "linkedlist.h"
#include "object.h"
#include "verticeList.h"
#include "faceList.h"
#include "numList.h"

  #define ERROR_STR_MAX 256
  size_t ERROR_STR_N = ERROR_STR_MAX;
  char error_str[ERROR_STR_MAX];
  
  unsigned int line = 0;
  unsigned int v_num = 0;
  int yylex();
  extern char *yytext;
  void yyerror(char *s);
  
  linkedList * objectList;
  linkedList * vertices;
  linkedList * faces;
  linkedList * facesNumList;
  linkedListNode * objectListNode;
  linkedListNode * facesListNode;
  linkedListNode * facesNumListNode;
  linkedListNode * verticesListNode;
  linkedListNode * verticeNumListNode;
  
  vertice tempVertice;
  vertice * tempVerticePtr;
  
  int firstFace;

  typedef unsigned long int face_t;
  void storeFace(face_t number);
  
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
MTLLIB STRING { /*printf("Load Material library: %s\n", $2);*/ }
| USEMTL STRING { /*printf("Use Material: %s\n",$2);*/ }
| USEMTL { /*printf("Use Material: %s\n",$2);*/ }
| OBJECT STRING {
  /*
  printf("New object: %s\n", $2);
  */
  objectListNode = addNewNode(objectList);
 }
| VERT NUMBER NUMBER NUMBER { 

  ++v_num;
  /*
  printf("#%u ",v_num);
  printf("Vertex: %f %f %f\n",$2,$3,$4);
  */

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

  /*List of faces comes after vertices*/
  firstFace = 1;
 }
| FACE facenumberlist { firstFace = 1; /*printf("face\n");*/ /*printf("Face(4) %f %f %f\n",$2,$3,$4);*/ }
| ELL NUMBER NUMBER { /**/ }
| TEXTURE NUMBER NUMBER {   }
| SETTING STRING { /*printf("Setting: %s\n",$2);*/ }
| SETTING NUMBER { /*printf("Setting: %s\n",$2);*/ }
;

facenumberlist: 
| facenumberlist NUMBER
{
  storeFace((face_t)$2);
  /*printf("%lu ", (face_t)$2);*/
}
| facenumberlist NUMBER SLASH NUMBER
{ 
  storeFace((face_t)$2);
  /*printf("%lu(%lu) ", (face_t)$2, (face_t)$4);*/
}
;

%%

void storeFace(face_t number)
{
  if(number>v_num) {
    snprintf(error_str, ERROR_STR_N, "Error: Trying to store face number %lu, but no vertice %lu was defined\n",number,number);
    yyerror(error_str);
  }
  
  if(objectListNode != 0)
    {
      faces = getFacesList(objectListNode);
      if(faces != 0)
	{
	  if(firstFace) {
	    facesListNode = addNewNode(faces);
	  }
	  facesNumList = getVerticeNums(facesListNode);
	  facesNumListNode = addNewNode(facesNumList);
	  storeNumListData(facesNumListNode, number);
	} else yyerror("Error: Cannot store face data\n");
    } else yyerror("Error: No object was defined\n");
  firstFace = 0;

}

int main(int argc, char **argv)
{  
  unsigned int i,n,nums,a,nfaces,b;
  unsigned long int * fdata;

  objectList = createNewObjectList();

  if(parseParams(argc, argv))
    {
      return 0;
    }
  yyparse();

  /*********/
  n = getNumNodes(objectList);
  printf("/*List: %u objects*/\n",n);
  objectListNode = getFirstNode(objectList);
  i=0;
  while(i<n) {
    if(objectListNode != 0) {
      vertices = getVerticeList(objectListNode);
      faces = getFacesList(objectListNode);
      nums = getNumNodes(faces);
      facesListNode = getFirstNode(faces);
      printf("/*\n Object #%u\n -> Vertices: %u\n -> Faces: %u\n*/\n", i, getNumNodes(vertices), getNumNodes(faces));
      a=0;
      while(a<nums) {
	facesNumList = getVerticeNums(facesListNode);
	nfaces = getNumNodes(facesNumList);
	printf("/*Node #%u of %u = %u*/\n",getIndexOfNode(facesListNode), nums, nfaces);
	verticeNumListNode = getFirstNode(facesNumList);
	b=0;
	while(b<nfaces) {
	  fdata = getVerticeNumListData(verticeNumListNode);
	  verticesListNode = getLinkedListNodeByIndex(vertices, *fdata-1);
	  tempVerticePtr = getVerticeData(verticesListNode);
	  printf("/*#%lu*/ glVertex3f(%f,%f,%f);\n",*fdata,tempVerticePtr->x,tempVerticePtr->y,tempVerticePtr->z);
	  verticeNumListNode = getNextLinkedListNode(verticeNumListNode);
	  b++;
	}
	printf("\n");
	facesListNode = getNextLinkedListNode(facesListNode);
	a++;
      }

    }
    objectListNode = getNextLinkedListNode(objectListNode);
    i++;
  }
  /*********/
  
  freeList(objectList);

  return 0;
}

void yyerror(char *s)
{
  printf("error: %s at line %u\n", s, line);
}
