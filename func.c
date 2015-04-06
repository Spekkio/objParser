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
#include <string.h>

#include "func.h"

unsigned int pFlags;

int parseParams(const int argc, char **argv)
{
  int i=0;
  pFlags = 0;
  while(i<argc) {

    if(strncmp("--stdin",argv[i], 7)==0)
      {
	pFlags = pFlags | PFLAG_STDIN;
      }

    if(strncmp("--stdout",argv[i], 8)==0)
      {
	pFlags = pFlags | PFLAG_STDOUT;
      }

    if(strncmp("--gui",argv[i], 5)==0)
      {
	pFlags = pFlags | PFLAG_GUI;
      }

    if(strncmp("--version",argv[i], 9)==0)
      {
	return 1;
      }

    i++;
  }
  return 0;
}
