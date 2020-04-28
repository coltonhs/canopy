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
#ifndef VECTOR2
#define VECTOR2
/***************************************************************************/
class vector2
{
  public:
    vector2(int a, int b) { x = a; y = b; }
    int x, y;

    void rotateBranch(float angle)
    {
      float a = x * cos(angle) - y * sin(angle);
      float b = x * sin(angle) + y * cos(angle);;

      x = static_cast<int>( a );
      y = static_cast<int>( b );
    }
};
/***************************************************************************/
#endif
