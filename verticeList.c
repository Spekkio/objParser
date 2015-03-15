#include <stdlib.h>
#include "linkedlist.h"
#include "verticeList.h"

struct vert {
  double x,y,z;
};

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
