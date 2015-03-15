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
  
  if(p!=0) {
    if(p->name!=0)
      free(p->name);
    
    freeList(p->vertices);
    freeList(p->faces);
    free(p);
  }
}

void * newObject(void)
{
  struct object * o;
  o = malloc(sizeof(struct object));

  o->vertices = createVerticeList();
  o->faces = createVerticeList(); /* todo */

  o->name = 0;
  return o;
}

linkedList * createNewObjectList(void)
{
  linkedList * list;
  
  list = newLinkedList(newObject, freeObject);

  return list;
}

linkedList * getVerticeList(linkedListNode * node)
{
  struct object * ptr;
  ptr = getNodeDataPtr(node);
  return ptr->vertices;
}

linkedList * getFacesList(linkedListNode * node)
{
  struct object * ptr;
  ptr = getNodeDataPtr(node);
  return ptr->faces;
}
