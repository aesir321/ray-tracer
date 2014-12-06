#include "RGBColour.h"

/* TODO
	* Brightness
	* reflective
	* shinyness?
	* How to combine colours
	*/

RGBColour::RGBColour()
{
	Red = 0;
	Green = 0;
	Blue = 0;
}

RGBColour::RGBColour(double red, double green, int blue)
{
	Red = red;
	Green = green;
	Blue = blue;
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

RGBColour RGBColour::operator/(const RGBColour &rhs)
{
	RGBColour temp;
	temp.Red = Red / rhs.Red;
	temp.Green = Green / rhs.Green;
	temp.Blue = Blue  / rhs.Blue;

	return temp;
}

RGBColour RGBColour::operator/(const double &rhs)
{
	RGBColour temp;
	temp.Red = Red / rhs;
	temp.Green = Green / rhs;
	temp.Blue = Blue / rhs;

	return temp;
}


bool RGBColour::operator==(const RGBColour &rhs)
{
	bool equal = false;
	if (Red == rhs.Red && Blue == rhs.Blue && Green == rhs.Green)
	{
		equal = true;
	}

	return equal;
}
