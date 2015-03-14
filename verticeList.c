#include <stdlib.h>
#include "linkedlist.h"

struct vert {
  double x,y,z;
};

void freeVertice(void * v)
{
  free(v);
}

void * newVertice(void)
{
  struct vert * v;
  v = malloc(sizeof(struct vert));
  return v;
}

void test()
{
  linkedList * list;
  linkedListNode * node;

  list = newLinkedList();
  node = newLinkedListNode(newVertice, freeVertice);

  addNode(list, node);

  freeList(list);
}
