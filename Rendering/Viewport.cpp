#include "Viewport.h"
#include <math.h>

Viewport::Viewport()
{
  _width = 1.0;
  _height = 1.0;
  _numberXPixels = 500;
  _numberYPixels = 500;
  _centre = Vector(0, 0, 10);
}

Viewport::Viewport(double width, double height, int numberXPixels, int numberYPixels, Vector centre)
{
  _width = width;
  _height = height;
  _numberXPixels = numberXPixels;
  _numberYPixels = numberYPixels;
  _centre = centre;
}

Viewport::~Viewport()
{

}

double Viewport::Height()
{
	return _height;
}

double Viewport::Width()
{
	return _width;
}

double Viewport::XPixels()
{
	return _numberXPixels;
}

double Viewport::YPixels()
{
	return _numberYPixels;
}

Vector Viewport::Position()
{
	return _centre;
}