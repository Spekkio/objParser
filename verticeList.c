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

void createVerticeList()
{
  linkedList * verticeList;
  linkedListNode * verticeNode;

  verticeList = newLinkedList(newVertice, freeVertice);
  verticeNode = newLinkedListNode(verticeList);

  addNode(verticeList, verticeNode);

  freeList(verticeList);
}
