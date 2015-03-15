typedef struct vert vertice;

struct vert {
  double x,y,z;
};

linkedList * createVerticeList();
void storeVerticeData(linkedListNode * node, const vertice new);
