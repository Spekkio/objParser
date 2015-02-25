#include <stdio.h>
#include <string.h>

void printglVertex3f(const float a, const float b, const float c)
{
  printf("glVertex3f(%f, %f, %f);\n",a,b,c);
}

int parseParams(const int argc, char **argv)
{
  int i=0;
  while(i<argc) {

    if(strncmp("--glvertex",argv[i], 10)==0)
      {
	printf("use glvert\n");
      }

    if(strncmp("--version",argv[i], 9)==0)
      {
	return 1;
      }

    i++;
  }
  return 0;
}
