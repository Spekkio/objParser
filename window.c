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

/*
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gdk/gdkkeysyms.h>

#include "linkedlist.h"
#include "func.h"
#include "main.h"

unsigned int quitting = 0;
unsigned int loadingObj = 1;

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

static gboolean on_key_press(GtkWidget *widget __attribute__((__unused__)), GdkEventKey *event, gpointer data __attribute__((__unused__)))
{
  if(event->type & GDK_KEY_PRESS)
    {
      switch(event->keyval)
	{
	case GDK_w:
	  printf("Pressed W\n");
	  break;
	default:
	  break;
	}
    }
  else if(event->type & GDK_KEY_RELEASE)
    {
      switch(event->keyval)
	{
	case GDK_w:
	  printf("Released W\n");
	  break;
	default:
	  break;
	}
    }
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
  g_signal_connect(window, "key_press_event", G_CALLBACK(on_key_press), NULL);

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
  glc = glXCreateContext(disp, vi, NULL, GL_TRUE);
  if(glc == NULL)
    {
      printf("\n\tCannot create gl context\n");
      exit(0);
    }

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
  doGlVertexList(objectList,paramScale,doGlVertex,doGlFaceSize, doGlEndList);
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
*/

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include <math.h>

#include "linkedlist.h"
#include "func.h"
#include "main.h"

#define X_WIDTH 800
#define Y_HEIGHT 600
#define WINDOW_BPP 32

#define RDELAY 20
#define WALK_SPEED (1.0/10.0)
#define MOUSEX_SPEED 0.1
#define MOUSEY_SPEED 0.1

/*Move defines*/
#define FORWARD 1
#define BACK    2
#define LEFT    4
#define RIGHT   8
#define JUMP    16
#define MOUSE   32
#define UP      64
#define DOWN    128

unsigned int loadingObj = 1;

/* Movement Variables */
int mousex,mousey,forward,strafe;
float xd, yd, zd;
float x_position;
float y_position; /*!< y_pos    */
float z_position;
int move_flags;

/* GLX */
GLuint glObject;

void resetCam()
{
  glLoadIdentity();
  glRotatef(yd, 1.0, 0.0, 0.0);
  glRotatef(xd, 0.0, 1.0, 0.0);
  glTranslatef(0.0, 0.0,-10.0);
  
  glTranslatef(x_position, z_position, y_position);
}

void move_calcs(void)
{
  float speed;

  speed=3.75/(RDELAY);

  /*do some movement calculations, based on what buttons are pressed down*/

  if(mousex!=0 || mousey!=0) {
    xd-=mousex*MOUSEX_SPEED;
    yd-=mousey*MOUSEY_SPEED; /*not inverted, + for inverted*/
    mousex=0;
    mousey=0;
  }
  /*xor, didn't work*/
  /*if((((move_flags&FORWARD)) ^ ((move_flags&BACK))) & 1) {*/

  if(move_flags&FORWARD)  {
    y_position+=speed*cos((xd/360.0)*2.0*3.14)*WALK_SPEED; /*forward*/
    x_position-=speed*sin((xd/360.0)*2.0*3.14)*WALK_SPEED; /*strafe*/
  }
  if(move_flags&BACK) {
    y_position+=-speed*cos((xd/360.0)*2.0*3.14)*WALK_SPEED; /*forward*/
    x_position-=-speed*sin((xd/360.0)*2.0*3.14)*WALK_SPEED; /*strafe*/
  }

  if(move_flags&UP) {
    z_position+=-speed*WALK_SPEED;
  }
  if(move_flags&DOWN) {
    z_position-=-speed*WALK_SPEED;
  }
  
  /*xor, didn't work*/
  /*if((((move_flags&LEFT)) ^ ((move_flags&RIGHT))) & 1) {*/

  if(move_flags&RIGHT) {

    if((move_flags&FORWARD) || (move_flags&BACK)) {
      speed/=2.0; /*if moving diagonal*/
    }

    y_position+=speed*cos(((xd+90.0)/360.0)*2.0*3.14)*WALK_SPEED;
    x_position-=speed*sin(((xd+90.0)/360.0)*2.0*3.14)*WALK_SPEED;
  }
  if(move_flags&LEFT) {

    if((move_flags&FORWARD) || (move_flags&BACK)) {
      speed/=2.0; /*if moving diagonal*/
    }

    y_position+=-speed*cos(((xd+90.0)/360.0)*2.0*3.14)*WALK_SPEED;
    x_position-=-speed*sin(((xd+90.0)/360.0)*2.0*3.14)*WALK_SPEED;
  }
}

/**
 * Callback function used in doGlVertexList().
 * The function for drawing a vertex.
 */
void doGlVertex(const double x, const double y, const double z)
{
  glVertex3f(x,y,z);
}

/**
 * Callback function used in doGlVertexList().
 * Tells how many vertices one polygon has
 * and calls the correct glBegin() function
 * based on that information.
 */
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

/**
 * Callback function used in doGlVertexList()
 * for the end of an object.
 */
void doGlEndList(void)
{ 
  glEnd();
}

/**
 * The SDL OpenGL display function
 */
void display(void)
{
  /*
  printf ("xv: %.4f, yv: %.4f, xpos: %.4f, ypos: %.4f\n",xd,yd,x_position,y_position);
  */

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  resetCam();
  /*glTranslatef(0.0, 10.0, 0.0);*/
  glCallList(glObject);
}

/**
 * The SDL main loop and SDL event handler.
 */
void mainLoop(void)
{
  SDL_Event event;
  int running=1, grab=0;
  Uint32 start, ticks,gticks;
  float collect;

  ticks = 0;
  collect = 0;
  start = 0;

  move_flags = 0;

  while(running)
    {
      gticks= SDL_GetTicks();
      ticks = gticks-start;
      start = gticks;

      while(SDL_PollEvent(&event))
	{
	  switch(event.type)
	    {
	    case SDL_QUIT:
              running=0;
              break;
	      
	    case SDL_MOUSEMOTION:
	      if(grab) {
		mousex = event.motion.xrel;
		mousey = event.motion.yrel;
		SDL_WarpMouse(X_WIDTH/2, Y_HEIGHT/2);
		move_flags|=MOUSE;
	      }
	      break;

	    case SDL_MOUSEBUTTONDOWN:
	      grab=1;
	      SDL_ShowCursor(0);
	      SDL_WM_GrabInput( SDL_GRAB_ON );
	      break;

	    case SDL_MOUSEBUTTONUP:
	      grab=0;
	      SDL_ShowCursor(1);
	      SDL_WM_GrabInput( SDL_GRAB_OFF );
	      break;

	    case SDL_KEYDOWN:
              switch(event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                  running=0;

		case SDLK_e:
		  move_flags|=UP;
		  break;
		case SDLK_q:
		  move_flags|=DOWN;
		  break;
		  
		case SDLK_w:
		  move_flags|=FORWARD;
		  break;
		case SDLK_s:
                  move_flags|=BACK;
                  break;
                case SDLK_d:
                  move_flags|=RIGHT;
                  break;
                case SDLK_a:
                  move_flags|=LEFT;
                  break;

		default: break;
		}
	      break;

	    case SDL_KEYUP:
              switch(event.key.keysym.sym)
                {

                case SDLK_e:
                  move_flags&=0xFFFFFFFF^(UP);
                  break;
                case SDLK_q:
                  move_flags&=0xFFFFFFFF^(DOWN);
                  break;

                case SDLK_s:
                  move_flags&=0xFFFFFFFF^(BACK);
                  break;
                case SDLK_w:
                  move_flags&=0xFFFFFFFF^(FORWARD);
                  break;
                case SDLK_a:
                  move_flags&=0xFFFFFFFF^(LEFT);
                  break;
                case SDLK_d:
                  move_flags&=0xFFFFFFFF^(RIGHT);
                  break;
                default:break;
                }
	      break;
	    default:break;
	    }
	}
      display();
      SDL_GL_SwapBuffers();

      collect+=ticks;
      if(collect>RDELAY) {
        move_calcs();
	collect=0;
      }
    }
}

int initGL(void)
{
  float aspect_ratio;
  GLenum res;

  x_position=y_position=z_position=0.0;
  yd=xd=zd=0.0;

  /*Init GLEW*/
  res = glewInit();
  if(res != GLEW_OK)
    {
      printf("Error: glewInit() '%s'\n",glewGetErrorString(res));
      return -1;
    }

  /*
  compileShaders();
  */
  
  /*Settings*/
  glShadeModel(GL_SMOOTH);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable( GL_BLEND );

  glClearDepth(1.0);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  /*Clear screen*/
  glClearColor(0.0, 0.0, 0.0, 1.0);
  /*
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);  
  */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  aspect_ratio = 800.0f/600.0f;
  gluPerspective(70.0, aspect_ratio, 0.001, 500.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  loadingObj = 1;
  glObject = glGenLists(1);
  glNewList(glObject, GL_COMPILE);
  glColor4f(1.0, 1.0, 1.0, 0.5);
  doGlVertexList(objectList,paramScale,doGlVertex,doGlFaceSize,doGlEndList);
  glEndList();
  loadingObj = 0;

  /*VBO, lookup how this is done*/
  /*
  vtest[0].x = 0.1;
  vtest[0].y = 0.2;
  vtest[0].z = 0.3;

  vtest[1].x = 0.1;
  vtest[1].y = 0.2;
  vtest[1].z = 0.3;

  vtest[2].x = 0.1;
  vtest[2].y = 0.2;
  vtest[2].z = 0.3;

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vtest), vtest, GL_STATIC_DRAW);
  */

  return 0;
}

int initSDL(void)
{
  SDL_Surface *screen;
  
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
      fprintf(stderr,"Error: SDL_Init(SDL_INIT_EVERYTHING) < 0\n");
      return -1;
    }
  
  screen=SDL_SetVideoMode(X_WIDTH,Y_HEIGHT,WINDOW_BPP,SDL_SWSURFACE|SDL_OPENGL);
  if(screen == 0)
    {
      fprintf(stderr,"error: SDL_SetVideoMode() == 0\n");
      return -1;
    }
  
  mousey=mousex=0;
  
  if(initGL()!=0)
    return -1;

  mainLoop();

  SDL_Quit();

  return 0;
}
