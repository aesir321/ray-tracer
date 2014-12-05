#ifndef RGBC_H
#define RGBC_H

#include "EasyBMP.h"

class RGBColour : public RGBApixel
{
public:
	RGBColour();
	RGBColour(int r, int g, int b);
	~RGBColour();
	RGBColour operator*(const RGBColour& rhs);
	RGBColour operator/(const RGBColour& rhs);
	RGBColour operator+(const RGBColour& rhs);
	RGBColour operator*(const double& rhs);
};

#endif