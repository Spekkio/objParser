
extern linkedList * objectList;

void doGlVertexList(linkedList * objList, double scale, void (*doVertex) (const double x, const double y, const double z), void (doFaceSize) (const unsigned int), void (*doEndList) (void));
