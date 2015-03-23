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
  return (linkedList *)newLinkedList(newNumList, freeNumList);
}

void storeNumListData(linkedListNode * ptr, const unsigned long int n)
{
  unsigned long int * data;
  data = getNodeDataPtr(ptr);
  *data = n;
}

unsigned long int * getVerticeNumListData(linkedListNode * ptr)
{
  unsigned long int * p;
  p = getNodeDataPtr(ptr);
  return p;
}
