//
//
//
//
//
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
void drawLineBresenham(int xStart, int yStart, int xEnd, int yEnd)
{
	int dx = abs(xEnd-xStart);
  int sx = xStart<xEnd ? 1 : -1;
	int dy = abs(yEnd-yStart);
  int sy = yStart<yEnd ? 1 : -1;
	int err = (dx>dy ? dx : -dy)/2;
  int e2;
  
	for(;;){
	    drawPixel(xStart,yStart);
	    if(xStart==xEnd && yStart==yEnd) break;
	    e2 = err;
	    if(e2>-dx){err -=dy; xStart+=sx;}
	    if(e2 <dy){err+=dx;yStart+=sy;}
	}
}

/***************************************************************************/