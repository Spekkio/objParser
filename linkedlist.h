typedef struct node linkedListNode;
typedef struct list linkedList;

void * newLinkedList(void * (*createFunction) (void), void (*freeFunction) (void * ptr));
linkedListNode * newLinkedListNode(linkedList * list);
void addNode(linkedList * list, linkedListNode * node);
void freeList(void * list_in);
