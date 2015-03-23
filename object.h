typedef struct object object_t;

struct object {
  linkedList * vertices;
  linkedList * faces;
  char * name;
};

linkedList * createNewObjectList();
linkedList * getVerticeList(linkedListNode * node);
linkedList * getFacesList(linkedListNode * node);
linkedListNode * getLinkedListNodeByVerticeNumber(linkedList * ptr, const unsigned int n);
