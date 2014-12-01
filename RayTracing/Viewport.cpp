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
	Vector temp = ray - sphere.Centre();
	double b = 2.0 * ray.ScalarProduct(temp);	
	double c = pow(temp.Magnitude(), 2) - pow(sphere.Radius(), 2);

	double root1 = 0.0;
	double root2 = 0.0;
	double discriminant = 0.0;
	double minRoot = 0.0;

	discriminant = pow(b, 2) - (4 * a * c);

	if (discriminant > 0)
    {
      root1 = (b * sqrt(discriminant)) / (2 * a);
      root2 = (- b * sqrt(discriminant)) / (2 * a);

	  // Check logic about min root.  Smallest should be closest to the origin?	
	  if (root1 < 0.0 && root2 < 0.0)
	  {
		  minRoot = -1.0;
	  }
	  else if (root1 > 0.0 && root2 > 0.0)
	  {
		  if (root1 < root2) //can't be negative
		  {
			  minRoot = root1;
		  }
		  else if (root2 < root1)
		  {
			  minRoot = root2;
		  }
	  }
	  else if (root1 > 0.0 && root2 < 0.0)
	  {
		  minRoot = root1;
	  }
	  else if (root2 > 0.0 && root1 < 0.0)
	  {
		  minRoot = root2;
	  }
    }
	else if (discriminant == 0)
    {
      root1 = (b * sqrt(discriminant)) / (2 * a);
	  if (root1 > 0)
	  {
		  minRoot = root1;
	  }
	  else
	  {
		  minRoot = -1.0;
	  } 
    }
	else
    {
		// Negative root means it is behind the viewport?
		minRoot = -1.0;
    }	
	return minRoot; //Does it make any sense to have this here or better on a shape?  Each line and shape will have its own intersection.
}

Vector Viewport::Centre()
{
	//set it a distance 1 away from the observer by default.
	Vector temp(0, 0, 1, true);
	return temp;
}