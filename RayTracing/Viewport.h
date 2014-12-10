#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "Ray.h"
#include "Sphere.h"

class Viewport
{
public:

	Viewport();
	Viewport(double width, double height, int numberXPixels, int numberYPixels, Vector centre);
	~Viewport();

	double Width();
	double Height();
	double XPixels();
	double YPixels();
	Vector Position();


private:

	double _width;
	double _height;
	int _numberXPixels;
	int _numberYPixels;
	Vector _centre;
};

#endif
