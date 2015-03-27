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

typedef struct node linkedListNode;
typedef struct list linkedList;

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

linkedListNode * getNextLinkedListNode(linkedListNode * list);
linkedListNode * getLinkedListNodeByIndex(linkedList * list, const unsigned int index);
void * newLinkedList(void * (*createFunction) (void), void (*freeFunction) (void * ptr));
linkedListNode * newLinkedListNode(const linkedList * list);
void addNode(linkedList * list, linkedListNode * node);
linkedListNode * addNewNode(linkedList * list);
void freeList(void * list_in);
unsigned int getNumNodes(const linkedList * p);
void * getNodeDataPtr(linkedListNode * p);
unsigned int getIndexOfNode(linkedListNode * p);
linkedListNode * getFirstNode(linkedList * p);
linkedListNode * getLastNode(linkedList * p);
