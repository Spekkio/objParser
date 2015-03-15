typedef struct node linkedListNode;
typedef struct list linkedList;

void * newLinkedList(void * (*createFunction) (void), void (*freeFunction) (void * ptr));
linkedListNode * newLinkedListNode(const linkedList * list);
void addNode(linkedList * list, linkedListNode * node);
linkedListNode * addNewNode(linkedList * list);
void freeList(void * list_in);
unsigned int getNumNodes(const linkedList * p);
