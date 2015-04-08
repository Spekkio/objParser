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
#include <string.h>
#include "simpleVerticeList.h"

#define VERTICE_BLOCK 26000

struct simpleVertice * simpleVerticeList;
size_t numVertices;
unsigned int vertCounter;

/*Allocate memory for ordered vertice List*/
struct simpleVertice * allocateSimpleVerticeList(void)
{
  numVertices = VERTICE_BLOCK;
  vertCounter = 0;
  simpleVerticeList = (struct simpleVertice *)malloc(calcSizeSimpleVerticeList(VERTICE_BLOCK));
  return simpleVerticeList;
}

struct simpleVertice * reallocateSimpleVerticeList(const size_t num)
{
  numVertices = num;
  simpleVerticeList = (struct simpleVertice *)realloc(simpleVerticeList, calcSizeSimpleVerticeList(num));  
  return simpleVerticeList;
}

struct simpleVertice * addVertice(struct simpleVertice * v)
{
  struct simpleVertice * r;
  if(vertCounter>=numVertices) {
    reallocateSimpleVerticeList(numVertices+VERTICE_BLOCK);
  }
  r=memcpy(&simpleVerticeList[vertCounter], v, sizeof(struct simpleVertice));
  /*simpleVerticeList[vertCounter] = *v;*/
  vertCounter++;
  return r;
}

void freeVerticeList()
{
  free(simpleVerticeList);
}

size_t calcSizeSimpleVerticeList(const size_t num)
{
  return sizeof(struct simpleVertice)*num;
}
