#include "RGBColour.h"

RGBColour::RGBColour()
{
	Red = 0;
	Green = 0;
	Blue = 0;
}

RGBColour::RGBColour(double r, double g, double b)
{
	Red = r;
	Green = g;
	Blue = b;
}

RGBColour::~RGBColour()
{

}

RGBColour RGBColour::operator*(const RGBColour &rhs)
{
	RGBColour temp;
	temp.Red = Red * rhs.Red;
	temp.Green = Green * rhs.Green;
	temp.Blue = Blue  * rhs.Blue;

	return temp;
}

RGBColour RGBColour::operator+(const RGBColour &rhs)
{
	RGBColour temp;
	temp.Red = Red + rhs.Red;
	temp.Green = Green + rhs.Green;
	temp.Blue = Blue + rhs.Blue;

	return temp;
}
RGBColour RGBColour::operator*(const double &rhs)
{
	RGBColour temp;
	temp.Red = Red * rhs;
	temp.Green = Green * rhs;
	temp.Blue = Blue  * rhs;

	return temp;
}
