#ifndef RGBC_H
#define RGBC_H

#include "../EasyBMP/EasyBMP.h"

class RGBColour
{
public:

	RGBColour();
	RGBColour(double red, double green, double blue);
	~RGBColour();

	RGBColour operator*(const RGBColour& rhs);
	RGBColour operator*(const double& rhs);
	RGBColour operator/(const RGBColour& rhs);
	RGBColour operator/(const double& rhs);
	RGBColour operator+(const RGBColour& rhs);
	RGBColour operator+(const double& rhs);	
	RGBColour operator-(const RGBColour& rhs);
	RGBColour operator-(const double& rhs);

	bool operator==(const RGBColour &rhs);

	RGBApixel Normalise();
	double Red();
	double Green();
	double Blue();

private :

	double _red;
	double _green;
	double _blue;
};

#endif
