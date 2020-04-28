/***************************************************************************/
//
// CPSC 4050 Final Group Project - Tree Canopy
// Professor Dhillon
// Spring 2020
//
// Claire Frommer
// Bryson Rudolph
// Colton Smith
//
/***************************************************************************/

/* Include needed files */
#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>   // The GL Utility Toolkit (Glut) Header

#include "vector2.h"

#define WIDTH 800
#define HEIGHT 600

// The starting length of a branch
float start_length = 100.0f;

// The factor to reduce the length of a branch by each iteration
float branch_reduction_factor = 0.75f;

// The angle that a branch is rotated by each iteration
float angle = M_PI/4;

// Translations
float xTranslate = 0.0;
float yTranslate = 0.0;
float zTranslate = 0.0;

float baseZVal = -900;
float baseYVal = -100;

// Other
bool displayAxes = false;


/***************************************************************************/
// Forward declarations
void drawLineDDA(float xStart, float yStart, float xEnd, float yEnd);
void drawLineBresenham(int xStart, int yStart, int xEnd, int yEnd);

void drawPixel(int x, int y);
void drawPixelColor(int x, int y, int r, int g, int b);

void branchLeft( vector2* sp, int len, float a);
void branchRight( vector2* sp, int len, float a);

/***************************************************************************/
void initWindow()
/* Clear the image area, and set up the coordinate system */
{
    glClearColor(0.0,0.0,0.0,0.0);
	  glShadeModel(GL_SMOOTH);
    // glOrtho(0,WIDTH,0,HEIGHT,-1.0,1.0);
    gluPerspective(60, (WIDTH/HEIGHT), 0, 1000);
}

/***************************************************************************/
void resetAllTransformVals()
{
  xTranslate = 0.0;
  yTranslate = 0.0;
  zTranslate = 0.0;
}

/***************************************************************************/
void resetDisplay()
{
  // First clear the screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  resetAllTransformVals();

  glLoadIdentity();
  initWindow();
  glTranslatef(0, 0, 0);
  /* To see the whole tree, first translate to our z val */
  glTranslatef(0, baseYVal, baseZVal);
}

/***************************************************************************/
void drawPixel(int x, int y)
/* Turn on the pixel found at x,y */
{
        glColor3f (1.0, 1.0, 1.0);
        glBegin(GL_POINTS);
           glVertex3i( x, y, 0);
        glEnd();
}
/***************************************************************************/
void drawPixelColor(int x, int y, int r, int g, int b)
/* Turn on the pixel found at x,y */
{
        glColor3f (r,g,b);
        glBegin(GL_POINTS);
           glVertex3i( x, y, 0);
        glEnd();
}

//***************************************************************************/
void branchLeft( vector2* start_point, int len, float a)
{
  len = len * branch_reduction_factor;
  if(len < 2) return;

  vector2 end_point(0,len);
  a+=angle;
  end_point.rotateBranch(a);
  end_point.x += start_point->x;
  end_point.y += start_point->y;
  drawLineBresenham(start_point->x,start_point->y,end_point.x,end_point.y);

  branchLeft(&end_point,len,a);
  branchRight(&end_point,len,a);
}

/***************************************************************************/
void branchRight( vector2* start_point, int len, float a)
{
  len = len * branch_reduction_factor;
  if(len < 2) return;

  vector2 end_point(0,len);
  a-=angle;
  end_point.rotateBranch(a);
  end_point.x += start_point->x;
  end_point.y += start_point->y;
  drawLineBresenham(start_point->x,start_point->y,end_point.x,end_point.y);

  branchLeft(&end_point,len,a);
  branchRight(&end_point,len,a);
}
/***************************************************************************/
void drawAxes()
{
  float maxAxisVal = 5000;
  // Y - Green
  glColor3f(0.0,255.0,0.0);
  glBegin(GL_LINES);
  glVertex3f(0, 0, 0);
  glVertex3f(0, maxAxisVal, 0);
  glEnd();

  // X - Red
  glColor3f(255.0,0.0,0.0);
  glBegin(GL_LINES);
  glVertex3f(0, 0, 0);
  glVertex3f(maxAxisVal, 0, 0);
  glEnd();

  // Z - Blue
  glColor3f(0.0,0.0,255.0);
  glBegin(GL_LINES);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, maxAxisVal);
  glEnd();
}

/***************************************************************************/
void display(void)   // Create The Display Function
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	      // Clear Screen

  // Draw axes
  if (displayAxes) { drawAxes();}

  // First do any needed translations
  glTranslatef(xTranslate, yTranslate, zTranslate);

  // vector2 start_point(WIDTH/2, 100);
  vector2 start_point(0, 100);
  drawLineBresenham(start_point.x,0,start_point.x,start_point.y);
  branchLeft(&start_point,start_length,0);
  branchRight(&start_point,start_length,0);

  // Reset our translations
  resetAllTransformVals();

  glutSwapBuffers();                                      // Draw Frame Buffer
}

/***************************************************************************/
void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
  // Define our translation val
  float translateVal = 5;

	switch ( key ) {
    case 'a':                        // Increase angle
      angle = angle * 1.05f;
      break;
    case 'A':                        // Decrease angle
      if(angle < M_PI)
      angle = angle / 1.05f;
      break;

    // Translations ///////////////////
    case 'i':
      xTranslate += translateVal;
      break;
    case 'I':
      xTranslate -= translateVal;
      break;
    case 'o':
      yTranslate += translateVal;
      break;
    case 'O':
      yTranslate -= translateVal;
      break;
    case 'p':
      zTranslate += translateVal;
      break;
    case 'P':
      zTranslate -= translateVal;
      break;
    case 27:
      resetDisplay();
      break;

    // ////////////////////////////////

    case 32:
      displayAxes = !displayAxes;
      break;

    default:
			break;
	}
}

/***************************************************************************/
int main (int argc, char *argv[])
{
	{
		glutInit            ( &argc, argv );
		glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
		glutInitWindowSize  ( WIDTH,HEIGHT );
		glutCreateWindow    ( "CG4050/6050 Final Project: Canopy Fractal" );

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

		glutDisplayFunc     ( display);
		glutIdleFunc	      ( display);
		glutKeyboardFunc    ( keyboard);
		initWindow();

    /* To see the whole tree, first translate to our z val */
    glTranslatef(0, baseYVal, baseZVal);

		glutMainLoop();
	}
}

/***************************************************************************/
