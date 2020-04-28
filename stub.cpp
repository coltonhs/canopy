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
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/***************************************************************************/
// Forward declarations
void drawPixel(int x, int y);
void drawPixelColor(int x, int y, int r, int g, int b);

/***************************************************************************/
void drawLineBresenham(int xStart, int yStart, int xEnd, int yEnd, int width)
{
	int j;
	int dx = abs(xEnd-xStart);
  int sx = xStart<xEnd ? 1 : -1;
	int dy = abs(yEnd-yStart);
  int sy = yStart<yEnd ? 1 : -1;
	int err = (dx>dy ? dx : -dy)/2;
  int e2;

	for(;;){
		 for (j = 0; j < width/2+1; j++) {
	    	drawPixel(xStart+j,yStart);
			drawPixel(xStart-j,yStart);
		 }
	    if(xStart==xEnd && yStart==yEnd) break;
	    e2 = err;
	    if(e2>-dx){err -=dy; xStart+=sx;}
	    if(e2 <dy){err+=dx;yStart+=sy;}
	}
}

/***************************************************************************/
