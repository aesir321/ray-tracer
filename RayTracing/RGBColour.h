#ifndef RGBC_H
#define RGBC_H

#include "EasyBMP.h"
/*
* TODO
* Normalise rgb values
*/

class RGBColour : public RGBApixel
{
public:
	RGBColour();
	RGBColour(double red, double green, double blue);
	~RGBColour();
	RGBColour operator*(const RGBColour& rhs);
	RGBColour operator/(const RGBColour& rhs);
	RGBColour operator/(const double& rhs);
	RGBColour operator+(const RGBColour& rhs);
	RGBColour operator*(const double& rhs);
	bool RGBColour::operator==(const RGBColour &rhs);
};

#endif