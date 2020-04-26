class vector2
{
  public:
    vector2(int a, int b) { x = a; y = b; }
     void rotate( float angle_r )
    {
      float _x = static_cast<float>( x ),
	          _y = static_cast<float>( y ),
	           s = sinf( angle_r ),
	           c = cosf( angle_r ),
	           a = _x * c - _y * s,
	           b = _x * s + _y * c;

	    x = static_cast<int>( a );
	    y = static_cast<int>( b );
    }
    int x, y;
};