#include <stdlib.h>
#include "linkedlist.h"
#include "numList.h"


void freeNumList(void *n)
{
  free(n);
}

void * newNumList(void)
{
  numList * n;
  n = malloc(sizeof(numList));
  return n;
}

linkedList * createNumList()
{
  return newLinkedList(newNumList, freeNumList);
}
