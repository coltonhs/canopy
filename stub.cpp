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
void drawPixelColor(int x, int y, float r, float g, float b);

bool colorOption1 = true;
bool colorOption2 = false;
bool colorOption3 = false;
bool colorOption4 = false;
bool colorOption5 = false;
bool colorOption6 = false;
/***************************************************************************/
void toggleColors()
{
  colorOption6 = colorOption5;
  colorOption5 = colorOption4;
  colorOption4 = colorOption3;
  colorOption3 = colorOption2;
  colorOption2 = colorOption1;
  colorOption1 = colorOption6;
}
/***************************************************************************/
void drawLineBresenham(int xStart, int yStart, int xEnd, int yEnd, int width, float lengthUpToStartPoint, int colorGradient)
{
  int j;
  int dx = abs(xEnd-xStart);
  int sx = xStart<xEnd ? 1 : -1;
  int dy = abs(yEnd-yStart);
  int sy = yStart<yEnd ? 1 : -1;
  int err = (dx>dy ? dx : -dy)/2;
  int e2;

  int pixelIter = 0;
  for(;;){
    for (j = 0; j < width/2+1; j++) {

      if(colorOption1) 
      {
        drawPixelColor(xStart+j,yStart, 0.0f, lengthUpToStartPoint / colorGradient + pixelIter * 1 / colorGradient, 
                       1.0f - (lengthUpToStartPoint / colorGradient + pixelIter * 1 / colorGradient));
        drawPixelColor(xStart-j,yStart, 0.0f, lengthUpToStartPoint / colorGradient + pixelIter * 1 / colorGradient, 
                       1.0f - (lengthUpToStartPoint / colorGradient + pixelIter * 1 / colorGradient));
      }
      else if(colorOption2)
      {
      	drawPixelColor(xStart+j,yStart, 0.0f, 1.0f - (lengthUpToStartPoint / colorGradient + pixelIter * 1 / colorGradient), 
                       lengthUpToStartPoint / colorGradient + pixelIter * 1 / colorGradient);
        drawPixelColor(xStart-j,yStart, 0.0f, 1.0f - (lengthUpToStartPoint / colorGradient + pixelIter * 1 / colorGradient), 
                       lengthUpToStartPoint / colorGradient + pixelIter * 1 / colorGradient);
      }
      else if(colorOption3)
      {
        drawPixelColor(xStart+j,yStart, 1.0f - (lengthUpToStartPoint / colorGradient + pixelIter * 1 / colorGradient), 
                       lengthUpToStartPoint / colorGradient + pixelIter * 1 / colorGradient, 0.0f);
        drawPixelColor(xStart-j,yStart, 1.0f - (lengthUpToStartPoint / colorGradient + pixelIter * 1 / colorGradient), 
                       lengthUpToStartPoint / colorGradient + pixelIter * 1 / colorGradient, 0.0f);
      }
      else if(colorOption4)
      {
        drawPixelColor(xStart+j,yStart, lengthUpToStartPoint / colorGradient + pixelIter * 1 / colorGradient,
                       1.0f - (lengthUpToStartPoint / colorGradient + pixelIter * 1 / colorGradient), 0.0f);
        drawPixelColor(xStart-j,yStart, lengthUpToStartPoint / colorGradient + pixelIter * 1 / colorGradient,
                       1.0f - (lengthUpToStartPoint / colorGradient + pixelIter * 1 / colorGradient), 0.0f);
      }
      else if(colorOption5)
      {
        drawPixelColor(xStart+j,yStart, lengthUpToStartPoint / colorGradient + pixelIter * 1 / colorGradient,
                       0.0f, 1.0f - (lengthUpToStartPoint / colorGradient + pixelIter * 1 / colorGradient));
        drawPixelColor(xStart-j,yStart, lengthUpToStartPoint / colorGradient + pixelIter * 1 / colorGradient,
                       0.0f, 1.0f - (lengthUpToStartPoint / colorGradient + pixelIter * 1 / colorGradient));
      }
      else if(colorOption6)
      {
      drawPixelColor(xStart+j,yStart, 1.0f - (lengthUpToStartPoint / colorGradient + pixelIter * 1 / colorGradient), 
                     0.0f, lengthUpToStartPoint / colorGradient + pixelIter * 1 / colorGradient);
      drawPixelColor(xStart-j,yStart, 1.0f - (lengthUpToStartPoint / colorGradient + pixelIter * 1 / colorGradient), 
                     0.0f, lengthUpToStartPoint / colorGradient + pixelIter * 1 / colorGradient);
      }
    }
    pixelIter++;

    if(xStart==xEnd && yStart==yEnd) break;
    e2 = err;
    if(e2>-dx){err -=dy; xStart+=sx;}
    if(e2 <dy){err+=dx;yStart+=sy;}
  }
}

/***************************************************************************/
