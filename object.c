#include <stdlib.h>
#include "linkedlist.h"
#include "verticeList.h"

struct object {
  linkedList * vertices;
  linkedList * faces;
  char * name;
};

void freeObject(void * ptr)
{
  struct object * p = (struct object *)ptr;
  free(p->name);
  freeList(p->vertices);
  freeList(p->faces);
  free(p);
}

void * newObject(void)
{
  struct object * o;
  o = malloc(sizeof(struct object));

  o->vertices = createVerticeList();

  o->name = 0;
  return o;
}

linkedList * createNewObjectList(void)
{
  linkedList * list;
  
  list = newLinkedList(newObject, freeObject);

  return list;
}
