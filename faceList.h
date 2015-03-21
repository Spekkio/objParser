typedef struct face facedata;

struct face {
  linkedList * vertices;
  linkedList * verticeNums;
  unsigned int numVertices;
};


linkedList * getVerticeNums(linkedListNode * node);
linkedList * createFaceList();

