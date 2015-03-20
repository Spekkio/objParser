#include <stdlib.h>
#include "linkedlist.h"
#include "faceList.h"
#include "numList.h"


void freeFace(void * v)
{
  facedata * f = (facedata *)v;
  freeList(f->vertices);
  freeList(f->verticeNums);
  free(f);
}

void * newFace(void)
{
  struct face * f;
  f = malloc(sizeof(struct face));
  f->vertices = createNumList();
  f->verticeNums = createNumList();
  return f;
}

linkedList * createFaceList()
{
  return newLinkedList(newFace, freeFace);
}
