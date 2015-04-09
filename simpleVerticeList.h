struct simpleVertice {
  double x,y,z;
};

extern struct simpleVertice * simpleVerticeList;
extern unsigned int vertCounter;

struct simpleVertice * allocateSimpleVerticeList(void);
struct simpleVertice * reallocateSimpleVerticeList(const size_t num);
struct simpleVertice * addVertice(struct simpleVertice * v);
size_t calcSizeSimpleVerticeList(const size_t num);
void freeVerticeList();
