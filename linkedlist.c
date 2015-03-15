#include <stdlib.h>
#include "linkedlist.h"

struct node {
  void * data;
  unsigned int index;
  linkedListNode *next;
  linkedListNode *prev;
};

struct list {
  linkedListNode * startNode;
  linkedListNode * lastNode;
  void (*freeFunction) (void * ptr);
  void * (*createFunction) (void);
  unsigned int numNodes;
};

void * newLinkedList(void * (*createFunction) (void), void (*freeFunction) (void * ptr))
{
  linkedList * new;
  new = malloc(sizeof(linkedList));
  new->startNode = (linkedListNode *)0;
  new->lastNode = (linkedListNode *)0;
  new->numNodes = 0;
  new->freeFunction = freeFunction;
  new->createFunction = createFunction;
  return new;
}

linkedListNode * newLinkedListNode(linkedList * list)
{
  linkedListNode * node;
  node = malloc(sizeof(linkedListNode));
  list->createFunction();
  node->index = -1;
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
  unsigned int i;
  linkedList * list = list_in;
  linkedListNode * node;
  node = list->startNode;

  i=0;
  while(i<list->numNodes)
    {
      list->freeFunction(node->data);
      node = node->next;
      i++;
    }

  free(list);
}
