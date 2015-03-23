#include <stdlib.h>
#include "linkedlist.h"
#include "verticeList.h"
#include "faceList.h"
#include "object.h"

void freeObject(void * ptr)
{
  object_t * p = (object_t *)ptr;
  
  if(p!=0) {
    if(p->name!=0)
      free(p->name);
    
    freeList(p->vertices);
    freeList(p->faces);
    free(p);
  }
}

void * newObject(void)
{
  object_t * o;
  o = malloc(sizeof(object_t));

  o->vertices = createVerticeList();
  o->faces = createFaceList(); /* todo */

  o->name = 0;
  return o;
}

linkedList * createNewObjectList(void)
{
  linkedList * list;
  
  list = newLinkedList(newObject, freeObject);

  return list;
}

linkedList * getVerticeList(linkedListNode * node)
{
  object_t * ptr;
  ptr = getNodeDataPtr(node);
  return ptr->vertices;
}

linkedList * getFacesList(linkedListNode * node)
{
  object_t * ptr;
  ptr = getNodeDataPtr(node);
  return ptr->faces;
}

linkedListNode * getLinkedListNodeByVerticeNumber(linkedList * ptr, const unsigned int n)
{
  unsigned int i;
  linkedListNode * tmpNode = ptr->startNode;
  vertice * tmpVertice;

  i=0;
  while(i<ptr->numNodes)
    {
      if(tmpNode != 0) {
	tmpVertice = getVerticeData(tmpNode);
	if(n == tmpVertice->verticeNumber)
	  {
	    return tmpNode;
	  }
	tmpNode = tmpNode->next;
	i++;
      }
    }
  return (linkedListNode *)0;
}
