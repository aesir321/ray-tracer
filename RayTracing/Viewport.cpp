#include "Viewport.h"

Viewport::Viewport()
{
  _width = 1.0;
  _height = 1.0;
}

Viewport::Viewport(double width, double height)
{
  _width = width;
  _height = height;
}

Viewport::~Viewport()
{
}

double Viewport::Intersection(Ray ray, Shape shape)
{
  //Store these coeffs on the shape...
  double a = 1.0;
  double b = 1.0;
  double c = 1.0;

  double root1 = 0.0;
  double root2 = 0.0;
  double discriminant = 0.0;

  discriminant = pow(b, 2) - (4 * a * c);

  if (discriminant > 0)
    {
      root1 = (b * sqrt(discriminant)) / (2 * a);
      root2 = (- b * sqrt(discriminant)) / (2 * a);
    }
  else if (discriminant == 0)
    {
      root1 = (b * sqrt(discriminant)) / (2 * a);
      root2 = root1;
    }
  else
    {
      //complex root and don't care, maybe error?
    }
  
  return 0.0; //Does it make any sense to have this here or better on a shape?  Each line and shape will have its own intersection.
}


