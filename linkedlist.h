typedef struct vert vertice;
typedef struct node linkedListNode;
typedef struct list linkedList;

void * newLinkedList(void);
linkedListNode * newLinkedListNode(void * (*createFunction) (void), void (*freeFunction) (void * ptr));
void addNode(linkedList * list, linkedListNode * node);
void freeList(void * list_in);
