/*
    objParser: converting Wavefront .obj format into OpenGL c-code
    Copyright (C) 2015  Daniel Hedeblom

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

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
