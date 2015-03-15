#include <stdlib.h>
#include "linkedlist.h"
#include "verticeList.h"

void freeVertice(void * v)
{
  free(v);
}

void * newVertice(void)
{
  vertice * v;
  v = malloc(sizeof(vertice));
  return v;
}

linkedList * createVerticeList()
{
  linkedList * verticeList;

  verticeList = newLinkedList(newVertice, freeVertice);

  return verticeList;
}

void storeVerticeData(linkedListNode * node, const vertice new)
{
  vertice * ptr;
  ptr = getNodeDataPtr(node);
  ptr->x = new.x;
  ptr->y = new.y;
  ptr->z = new.z;
}
