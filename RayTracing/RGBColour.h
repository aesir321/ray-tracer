#ifndef RGBC_H
#define RGBC_H

#include "EasyBMP.h"

class RGBColour : public RGBApixel
{
public:
	RGBColour();
	RGBColour(double r, double g, double b);
	~RGBColour();
	RGBColour RGBColour::operator*(const RGBColour& rhs);
	RGBColour RGBColour::operator+(const RGBColour& rhs);
	RGBColour RGBColour::operator*(const double& rhs);
};

#endif