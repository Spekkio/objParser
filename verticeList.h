typedef struct vert vertice;

struct vert {
  double x,y,z;
  unsigned long int verticeNumber;
};

linkedList * createVerticeList();
void storeVerticeData(linkedListNode * node, const vertice new);
vertice * getVerticeData(linkedListNode * ptr);
