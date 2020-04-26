//
//
//
//
//
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
    glOrtho(0,WIDTH,0,HEIGHT,-1.0,1.0);
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
  end_point.rotate(a);
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
  end_point.rotate(a);
  end_point.x += start_point->x;
  end_point.y += start_point->y;
  drawLineBresenham(start_point->x,start_point->y,end_point.x,end_point.y);
  
  branchLeft(&end_point,len,a);
  branchRight(&end_point,len,a);
}

/***************************************************************************/
void display(void)   // Create The Display Function
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	      // Clear Screen 
  
  vector2 start_point(WIDTH/2, 100);
  drawLineBresenham(start_point.x,0,start_point.x,start_point.y);
  branchLeft(&start_point,start_length,0);
  branchRight(&start_point,start_length,0);
  
  glutSwapBuffers();                                      // Draw Frame Buffer 
}

/***************************************************************************/
void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{

	switch ( key ) {
    case 'a':                        // Increase angle
      angle = angle * 1.05f;  
      break;   
    case 'A':                        // Decrease angle
      if(angle < M_PI)
      angle = angle / 1.05f;     
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
		glutDisplayFunc     ( display);  
		glutIdleFunc	      ( display);
		glutKeyboardFunc    ( keyboard);
		initWindow();
		glutMainLoop(); 
	}
}

/***************************************************************************/


