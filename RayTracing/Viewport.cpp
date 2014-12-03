#include "Viewport.h"
#include <math.h>

Viewport::Viewport()
{
	//Implement defaults here
  _width = 1.0;
  _height = 1.0;
}

Viewport::Viewport(double width, double height, int numberxPixels, int numberYPixels, Vector centre)
{
  _width = width;
  _height = height;
  _numberXPixels = numberxPixels;
  _numberYPixels = numberYPixels;
  _centre = centre;
}

Viewport::~Viewport()
{
}

double Viewport::GetDimension(int dimension) // 1=width, 2=height
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
	default:
		break;
	}

	return dim;
}

int Viewport::GetNumberOfPixels(int dimension) // 1=width, 2=height
{
	int dim = 0;

	switch (dimension)
	{
	case 1:
		dim = _numberXPixels;
		break;
	case 2:
		dim = _numberYPixels;
		break;
	default:
		break;
	}

	return dim;
}

Vector Viewport::Centre()
{
	//set it a distance 1 away from the observer by default.
	Vector temp(0, 0, 1, true);
	return temp;
}

Vector Viewport::GetPosition()
{
	return _centre;
}