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
  linkedList * list;
  linkedListNode * node;

  list = newLinkedList();
  node = newLinkedListNode(newVertice, freeVertice);

  addNode(list, node);

  freeList(list);
}
