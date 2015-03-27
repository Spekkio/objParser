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

void freeVertice(void * v)
{
  free(v);
}

void * newVertice(void)
{
  vertice * v;
  v = malloc(sizeof(vertice));
  return v;
}

linkedList * createVerticeList()
{
  linkedList * verticeList;

  verticeList = newLinkedList(newVertice, freeVertice);

  return verticeList;
}

void storeVerticeData(linkedListNode * node, const vertice new)
{
  vertice * ptr;
  ptr = getNodeDataPtr(node);
  ptr->x = new.x;
  ptr->y = new.y;
  ptr->z = new.z;
  ptr->verticeNumber = new.verticeNumber;
}

vertice * getVerticeData(linkedListNode * ptr)
{
  vertice * p;
  p = getNodeDataPtr(ptr);
  return p;
}


