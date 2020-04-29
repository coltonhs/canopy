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

// All of our default parameter values
#define DEFAULT_START_LENGTH 100.0
#define DEFAULT_BRANCH_LENGTH 2.0
#define DEFAULT_BRANCH_THICKNESS 1.0
#define DEFAULT_BRANCH_REDUCTION_FACTOR 0.75
#define DEFAULT_BRANCH_ROTATE_ANGLE (M_PI/4)
#define DEFAULT_COLOR_GRADIENT 350

// The starting length of a branch
float start_length = DEFAULT_START_LENGTH;

// The minimum length of a branch
float min_right_length = DEFAULT_BRANCH_LENGTH;
float min_left_length = DEFAULT_BRANCH_LENGTH;

// Branch Thickness
int right_thickness = DEFAULT_BRANCH_THICKNESS;
int left_thickness = DEFAULT_BRANCH_THICKNESS;
int thickness = DEFAULT_BRANCH_THICKNESS;

// The factor to reduce the length of a branch by each iteration
float branch_reduction_factor = DEFAULT_BRANCH_REDUCTION_FACTOR;

// The angle that a branch is rotated by each iteration
float right_angle = DEFAULT_BRANCH_ROTATE_ANGLE;
float left_angle = DEFAULT_BRANCH_ROTATE_ANGLE;

// Translations
float xTranslate = 0.0;
float yTranslate = 0.0;
float zTranslate = 0.0;
float zRotate = 0.0;

float baseZVal = -900;
float baseYVal = -100;

// Other
bool displayAxes = false;

// Color
int colorGradient = 350;


/***************************************************************************/
// Forward declarations
void drawLineDDA(float xStart, float yStart, float xEnd, float yEnd);
void drawLineBresenham(int xStart, int yStart, int xEnd, int yEnd, int width,
                       float lengthUpToStartPoint, int colorGradient);

void drawPixel(int x, int y);
void drawPixelColor(int x, int y, float r, float g, float b);

void branchLeft( vector2* sp, int len, float a);
void branchRight( vector2* sp, int len, float a);

void branchLeft( vector2* sp, int len, float a, float totalLen);
void branchRight( vector2* sp, int len, float a, float totaLen);

void toggleColors();

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
  zRotate = 0.0;
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
  glRotatef(zRotate, 0.0, 0.0, 1.0);
  glTranslatef(0, baseYVal, baseZVal);
}

/***************************************************************************/
void resetAll()
{
  // First reset all parameters to their default values
  start_length = DEFAULT_START_LENGTH;
  min_right_length = DEFAULT_BRANCH_LENGTH;
  min_left_length = DEFAULT_BRANCH_LENGTH;
  right_thickness = DEFAULT_BRANCH_THICKNESS;
  left_thickness = DEFAULT_BRANCH_THICKNESS;
  thickness = DEFAULT_BRANCH_THICKNESS;
  branch_reduction_factor = DEFAULT_BRANCH_REDUCTION_FACTOR;
  right_angle = DEFAULT_BRANCH_ROTATE_ANGLE;
  left_angle = DEFAULT_BRANCH_ROTATE_ANGLE;
  colorGradient = DEFAULT_COLOR_GRADIENT;

  // Then rest our display
  resetDisplay();
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
void drawPixelColor(int x, int y, float r, float g, float b)
/* Turn on the pixel found at x,y */
{
        glColor3f (r,g,b);
        glBegin(GL_POINTS);
           glVertex3i( x, y, 0);
        glEnd();
}
/***************************************************************************/
float calculateDistance(float x1,float x2, float y1, float y2)
{
  float distance = sqrt((pow(x2 - x1,2) + pow(y2 - y1,2)));
  return distance;
}
//***************************************************************************/
void branchLeft( vector2* start_point, int len, float a, float lengthUpToStartPoint)
{
  len = len * branch_reduction_factor;
  if(len < min_left_length) return;

  vector2 end_point(0,len);
  a+=left_angle;
  end_point.rotateBranch(a);
  end_point.x += start_point->x;
  end_point.y += start_point->y;
  drawLineBresenham(start_point->x,start_point->y,end_point.x,end_point.y,
  	left_thickness,lengthUpToStartPoint,colorGradient);

  lengthUpToStartPoint = lengthUpToStartPoint + calculateDistance(end_point.x, start_point->x, end_point.y, start_point->y);
  branchLeft(&end_point,len,a,lengthUpToStartPoint);
  branchRight(&end_point,len,a,lengthUpToStartPoint);
}

/***************************************************************************/
void branchRight( vector2* start_point, int len, float a, float lengthUpToStartPoint)
{
  len = len * branch_reduction_factor;
  if(len < min_right_length) return;

  vector2 end_point(0,len);
  a-=right_angle;
  end_point.rotateBranch(a);
  end_point.x += start_point->x;
  end_point.y += start_point->y;
  drawLineBresenham(start_point->x,start_point->y,end_point.x,end_point.y,
  	right_thickness,lengthUpToStartPoint,colorGradient);

  lengthUpToStartPoint = lengthUpToStartPoint + calculateDistance(end_point.x, start_point->x, end_point.y, start_point->y);
  branchLeft(&end_point,len,a,lengthUpToStartPoint);
  branchRight(&end_point,len,a,lengthUpToStartPoint);
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
  glRotatef(zRotate, 0.0, 0.0, 1.0);
  glTranslatef(xTranslate, yTranslate, zTranslate);

  // vector2 start_point(WIDTH/2, 100);
  vector2 start_point(0, 100);
  drawLineBresenham(start_point.x,0,start_point.x,start_point.y, thickness,0,colorGradient);
  branchLeft(&start_point,start_length,0,0);
  branchRight(&start_point,start_length,0,0);

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
    case 't':
      zRotate += 180.0f;
      yTranslate -= 330.0f;
      break;
    case 'T':
      zRotate -= 180.0f;
      break;
    case 'a':                                     	// Increase right angle
      right_angle = right_angle * 1.05f;
      break;
    case 'A':                             		// Decrease right angle
      if(right_angle < M_PI)
        right_angle = right_angle / 1.05f;
	break;
        case 's':					// Increase left angle
	  left_angle = left_angle * 1.05f;
	  break;
	case 'S':					 // Decrease left angle
	if(left_angle < M_PI)
	  left_angle = left_angle / 1.05f;
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
    // Branch Reduction Values //
    case 'd':
      branch_reduction_factor += .005;
      break;
    case 'D':
      branch_reduction_factor -= .005;
      break;
    // Minimum Branch Length //
    case 'q':
      min_right_length += 1.0f;
      break;
    case 'Q':
      if (min_right_length > 1.0)
        min_right_length -= 1.0f;
      break;
    case 'w':
      min_left_length += 1.0f;
      break;
    case 'W':
      if (min_left_length > 1.0)
        min_left_length -= 1.0f;
      break;
    case 'r':
      right_thickness += 1;
      break;
    case 'R':
      if (right_thickness > 1)
        right_thickness -= 1;
      break;
    case 'l':
      left_thickness += 1;
      break;
    case 'L':
      if (left_thickness > 1)
        left_thickness -= 1;
      break;
    case 'y':
      thickness += 1;
      break;
    case 'Y':
      if (thickness > 1)
        thickness -= 1;
      break;
    // Backspace
    case 8:
      resetDisplay();
      break;
    // Color
    case 'c':
      toggleColors();
      break;
    case 'v':
      if(colorGradient > 10)
      colorGradient = colorGradient - 10;
      break;
    case 'V':
      colorGradient = colorGradient + 10;
      break;
    // ESC
    case 27:
      resetAll();
      break;
    // Space bar
    case 32:
      displayAxes = !displayAxes;
      break;
    default:
      break;
  }
}

/***************************************************************************/
void printMenu()
{
	printf("Press...\n");
	printf("'a' to increase the right side angle of the branches\n");
	printf("'A' to decrease the right side angle of the branches\n");
	printf("'s' to increase the left side angle of the branches\n");
	printf("'S' to decrease the left side angle of the branches\n");
	printf("'i' to translate object right\n");
	printf("'I' to translate object left\n");
	printf("'o' to translate object up\n");
	printf("'O' to translate object down\n");
	printf("'p' to translate object towards the screen\n");
	printf("'P' to translate object away from the screen\n");
	printf("'d' to increase the branch reduction factor\n");
	printf("'D' to decrease the branch reduction factor\n");
  printf("'q' to increase the right side minimum branch length\n");
	printf("'Q' to decrease the right side minimum branch length\n");
	printf("'w' to increase the left side minimum branch length\n");
	printf("'W' to decrease the left side minimum branch length\n");
  printf("'t' to toggle between tree growing up and down\n");
	printf("'r' to increase right side branch thickness\n");
	printf("'R' to decrease right side branch thickness\n");
	printf("'l' to increase left side branch thickness\n");
	printf("'L' to decrease left side branch thickness\n");
	printf("'y' to increase trunk thickness\n");
	printf("'Y' to decrease trunk thickness\n");
        printf("'c' to toggle between color options\n");
        printf("'v' to increase color gradient (HOLD DOWN)\n");
        printf("'V' to decrease color gradient (HOLD DOWN)\n");
  printf("'BACKSPACE' to reset ONLY transformations\n");
  printf("'ESC' to reset ALL changes\n");
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

		printMenu();

		glutDisplayFunc     ( display);
		glutIdleFunc	      ( display);
		glutKeyboardFunc    ( keyboard);
		initWindow();

    /* To see the whole tree, first translate to our z val */
	 glRotatef(zRotate, 0.0, 0.0, 1.0);
    glTranslatef(0, baseYVal, baseZVal);

		glutMainLoop();
	}
}

/***************************************************************************/

