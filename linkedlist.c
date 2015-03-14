#include <stdlib.h>
#include "linkedlist.h"

struct node {
  void * data;
  unsigned int index;
  void (*freeFunction) (void * ptr);
  linkedListNode *next;
  linkedListNode *prev;
};

struct list {
  linkedListNode * startNode;
  linkedListNode * lastNode;
  unsigned int numNodes;
};

void * newLinkedList(void)
{
  linkedList * new;
  new = malloc(sizeof(linkedList));
  new->startNode = (linkedListNode *)0;
  new->lastNode = (linkedListNode *)0;
  new->numNodes = 0;
  return new;
}

linkedListNode * newLinkedListNode(void * (*createFunction) (void), void (*freeFunction) (void * ptr))
{
  linkedListNode * node;
  node = malloc(sizeof(linkedListNode));
  node->data = createFunction();
  node->index = -1;
  node->freeFunction = freeFunction;
  node->next = (linkedListNode *)0;
  node->prev = (linkedListNode *)0;

  return node;
}

void addNode(linkedList * list, linkedListNode * node)
{
  if(list->startNode==0) {
    list->startNode = node;
    list->lastNode = list->startNode;
    list->startNode->index = 0;
  }
  else {
    list->lastNode->next = node;
    list->lastNode = list->lastNode->next;
    list->startNode->index = list->lastNode->index+1;
  }
  list->numNodes++;
}

void freeList(void * list_in)
{
  int i;
  linkedList * list = list_in;
  linkedListNode * node;
  node = list->startNode;

  i=0;
  while(i<list->numNodes)
    {
      node->freeFunction(node->data);
      node = node->next;
      i++;
    }

  free(list);
}

