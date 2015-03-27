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
  f->numVertices = 0;
  return f;
}

linkedList * createFaceList()
{
  return newLinkedList(newFace, freeFace);
}

linkedList * getVerticeNums(linkedListNode * node)
{
  struct face * ptr;
  ptr = getNodeDataPtr(node);
  return ptr->verticeNums;
}
