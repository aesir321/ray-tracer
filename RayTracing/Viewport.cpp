#include "Viewport.h"
#include <math.h>

Viewport::Viewport()
{
  _width = 1.0;
  _height = 1.0;
}

Viewport::Viewport(double width, double height, double depth)
{
  _width = width;
  _height = height;
  _depth = depth;
}

Viewport::~Viewport()
{
}

double Viewport::GetDimension(int dimension) // 1=width, 2=height, 3=depth
{
	double dim = 0.0;

	switch (dimension)
	{
	case 1:
		dim = _width;
		break;
	case 2:
		dim = _height;
		break;
	case 3: 
		dim = _depth;
		break;
	default:
		break;
	}

	return dim;
}

double Viewport::Intersection(Ray ray, Sphere sphere)
{
  //Store these coeffs on the shape, put them here for now to test.
	double a = ray.ScalarProduct(ray);	
	double b = 2.0 * ray.ScalarProduct(ray - sphere.Centre());
	Vector temp = ray - sphere.Centre();
	double c = pow(temp.Magnitude(), 2);

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
	
	// Check logic about min root.  Smallest should be closest to the origin?
	double minRoot = 0.0;
	if (root1 < root2)
	{
		minRoot = root1;
	}
	else
	{
		minRoot = root2;
	}
	
	return minRoot; //Does it make any sense to have this here or better on a shape?  Each line and shape will have its own intersection.
}


