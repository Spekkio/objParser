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
