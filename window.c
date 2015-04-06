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

#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"
#include "main.h"

#define X_WIDTH 800
#define Y_HEIGHT 600
#define WINDOW_BPP 24

unsigned int quitting = 0;
unsigned int loadingObj = 1;

/* GTK */
GtkWidget * window;
GtkWidget * draw_area;
GdkVisual * visual;
GdkPixmap * pixmap;
GdkDisplay* pGtkDisplay;
Display * disp;
Window root;
XVisualInfo * vi;
Colormap cmap;
XWindowAttributes wa;

/* GLX */
GLXContext glc;
GLfloat rotation_matrix[16];
GLint att[]   = { GLX_RGBA, GLX_DEPTH_SIZE, WINDOW_BPP, GLX_DOUBLEBUFFER, None };
GLuint glObject;

void doGlVertex(const double x, const double y, const double z)
{
  glVertex3f(x,y,z);
}

void doGlFaceSize(const unsigned int nfaces)
{
  switch(nfaces) {
  case 1:
    glBegin(GL_POINTS);
    break;
  case 2:
    glBegin(GL_LINES);
    break;
  case 3:
    glBegin(GL_TRIANGLES);
    break;
  case 4:
    glBegin(GL_QUADS);
    break;
  default:
    glBegin(GL_POLYGON);
    break;
  }
}

void doGlEndList(void)
{ 
  glEnd();
}

void expose()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  /*
  glRotatef(yd, 1.0, 0.0, 0.0);
  glRotatef(xd, 0.0, 1.0, 0.0);
  */
  glTranslatef(0.0, 0.0,-10.0);
  
  glColor4f(1.0, 1.0, 1.0, 0.5);
  
  if(loadingObj==0) {
    glCallList(glObject);
  }

  glXSwapBuffers(disp, GDK_WINDOW_XID(window->window));
}

static gboolean time_handler(GtkWidget *widget)
{
  if(quitting==0)
    if(gtk_widget_is_drawable(widget))
      {
	XGetWindowAttributes(disp, GDK_WINDOW_XID(window->window), &wa);
	glViewport(0, 0, wa.width, wa.height);
	expose();
      }
  return TRUE;
}

static gboolean expose_event(GtkWidget *widget __attribute__((__unused__)), GdkEvent *event __attribute__((__unused__)), gpointer data __attribute__((__unused__)))
{
  expose();
  return FALSE;
}

static gboolean delete_event(GtkWidget *widget __attribute__((__unused__)), GdkEvent *event __attribute__((__unused__)), gpointer data __attribute__((__unused__)))
{
  quitting=1;
  glXMakeCurrent(disp, None, NULL);
  glXDestroyContext(disp, glc);
  gtk_main_quit();
  return FALSE;
}

void initRoutine()
{
  quitting=0;
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  draw_area = gtk_drawing_area_new();

  gtk_widget_set_size_request(draw_area, X_WIDTH, Y_HEIGHT);

  gtk_container_add(GTK_CONTAINER(window), draw_area);

  visual = gdk_visual_get_system();
  pixmap = gdk_pixmap_new(NULL, X_WIDTH, Y_HEIGHT, WINDOW_BPP);

  gtk_window_set_title(GTK_WINDOW(window), "objParser Viewer");
  gtk_window_set_default_size(GTK_WINDOW(window), X_WIDTH, Y_HEIGHT);

  g_timeout_add(1.0,(GSourceFunc)time_handler, GTK_WINDOW(window));

  g_signal_connect(window, "delete-event", G_CALLBACK(delete_event), NULL);
  g_signal_connect(window, "expose-event", G_CALLBACK(expose_event), NULL);

  pGtkDisplay = gtk_widget_get_display(window);
  disp = gdk_x11_display_get_xdisplay(pGtkDisplay);
  root = gdk_x11_get_default_root_xwindow();

  vi = glXChooseVisual(disp,0,att);
  if(vi == NULL)
    {
      printf("\n\tno matching visuals\n\n");
    }

  cmap = XCreateColormap(disp, root, vi->visual, AllocNone);
  if(cmap == 0)
    {
      printf("\n\tCannot create color map\n");
      exit(0);
    }  
}

void glxSetup()
{
  /*create a new GLX rendering context*/
  glc = glXCreateContext(disp, vi, NULL, GL_TRUE);
  if(glc == NULL)
    {
      printf("\n\tCannot create gl context\n");
      exit(0);
    }

  /*attach a GLX context to a window or a GLX pixmap*/
  glXMakeCurrent(disp, GDK_WINDOW_XID(window->window), glc);

  glShadeModel(GL_SMOOTH);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable( GL_BLEND );
  glClearDepth(1.0);


  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  glClearColor(0.0, 0.0, 0.0, 1.00);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  gluPerspective(70.0, 800.0f/600.0f, 1.0, 500.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  loadingObj = 1;
  glObject = glGenLists(1);
  glNewList(glObject, GL_COMPILE);
  doGlVertexList(objectList,1.0f,doGlVertex,doGlFaceSize, doGlEndList);
  glEndList();
  loadingObj = 0;

  glGetFloatv(GL_MODELVIEW_MATRIX, rotation_matrix);
}

void init_window(int argc, char **argv)
{
  gtk_init(&argc, &argv);

  initRoutine();
  gtk_widget_show(window);

  glxSetup();

  gtk_main(); 
}
