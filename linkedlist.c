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

linkedListNode * newLinkedListNode(const linkedList * list)
{
  linkedListNode * node;
  node = malloc(sizeof(linkedListNode));
  node->data = list->createFunction();
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

linkedListNode * addNewNode(linkedList * list)
{
  linkedListNode * node;
  node = newLinkedListNode(list);
  addNode(list,node);
  return node;
}

unsigned int getNumNodes(const linkedList * p)
{
  return p->numNodes;
}

void freeList(void * list_in)
{
  unsigned int i;
  linkedList * list = list_in;
  linkedListNode * node=0, * temp=0;
  
  if(list!=0) {
    node = list->startNode;
    i=0;
    while(i<list->numNodes)
      {
	if(node!=0) {
	  list->freeFunction(node->data); /* free the space of the data */
	  temp = node;
	  node = node->next;
	  free(temp); /* free the space of the node */
	}
	i++;
      }
    
    free(list);
  }
}

void * getNodeDataPtr(linkedListNode * p)
{
  return p->data;
}

unsigned int getIndexOfNode(linkedListNode * p)
{
  return p->index;
}

linkedListNode * getFirstNode(linkedList * p)
{
  return p->startNode;
}

linkedListNode * getLastNode(linkedList * p)
{
  return p->lastNode;
}
