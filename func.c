/*
    objParser: converting Wavefront .obj format into OpenGL c-code
    Copyright (C) 2015  Daniel Hedeblom

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "func.h"

unsigned int pFlags;

/*scaling parameter from command line*/
double paramScale;

void print_warning(const char * str, const unsigned int line)
{
  if(pFlags & PFLAG_WARNINGS) {
    fprintf(stderr,"Warning: %s @ line %u\n", str, line+1);
  }
}

int parseParams(const int argc, char **argv)
{
  int i=0;
  pFlags = 0;
  paramScale = 1.0f;
  while(i<argc) {
    
    if(strncmp("-stdin",argv[i], 6)==0)
      {
	pFlags = pFlags | PFLAG_STDIN;
      }
    else if(strncmp("-f",argv[i], 6)==0)
      {
	pFlags = pFlags | PFLAG_FILE;
      }

    if(strncmp("-scale",argv[i], 6)==0)
      {
	i++;
	paramScale = strtod(argv[i],NULL);
      }
    
    if(strncmp("-stdout",argv[i], 7)==0)
      {
	pFlags = pFlags | PFLAG_STDOUT;
      }

    if(strncmp("-gui",argv[i], 4)==0)
      {
	pFlags = pFlags | PFLAG_GUI;
      }

    if(strncmp("-w",argv[i], 2)==0)
      {
	pFlags = pFlags | PFLAG_WARNINGS;
      }

    if(strncmp("-version",argv[i], 8)==0)
      {
	return 1;
      }

    i++;
  }
  return 0;
}
