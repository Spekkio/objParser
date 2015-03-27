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
#include <stdio.h>
#include "linkedlist.h"

linkedListNode * getNextLinkedListNode(linkedListNode * list)
{
  return list->next;
}

linkedListNode * getLinkedListNodeByIndex(linkedList * list, const unsigned int index)
{
  unsigned int i;
  linkedListNode * tmpNode = list->startNode;

  i=0;
  while(i<list->numNodes)
    {
      if(tmpNode != 0) {
	if(tmpNode->index == index) {
	  return tmpNode;
	}
	tmpNode = tmpNode->next;
	i++;
      } else return (linkedListNode *)0;
    }
  return (linkedListNode *)0;
}

void * newLinkedList(void * (*createFunction) (void), void (*freeFunction) (void * ptr))
{
  linkedList * new;
  new = malloc(sizeof(linkedList));
  if(new == NULL)
    {
      fprintf(stderr, "Error: Out of memory\n");
      return 0;
    }
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
  if(node == NULL)
    {
      fprintf(stderr, "Error: Out of memory\n");
      return 0;
    }
  node->data = list->createFunction();
  node->index = -1;
  node->next = (linkedListNode *)0;
  node->prev = (linkedListNode *)0;

  return node;
}

void addNode(linkedList * list, linkedListNode * node)
{
  if(list->startNode==0) {
    node->prev = 0;
    node->next = 0;
    list->startNode = node;
    list->lastNode = list->startNode;
    list->startNode->index = 0;
  }
  else {
    list->lastNode->next = node;            /*Set the Next node to the new node */
    node->prev = list->lastNode;            /*Set the Prev node to the current last node*/
    list->lastNode = node;                  /*Set the LastNode to the new node */
    list->lastNode->index = list->numNodes; /*Set the Index*/
  }
  list->numNodes++;
}

linkedListNode * addNewNode(linkedList * list)
{
  linkedListNode * node;
  if(list!=0) {
    node = newLinkedListNode(list);
    addNode(list,node);
  } else return (linkedListNode *)0;
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
