#include "RGBColour.h"

/* TODO
	* Brightness
	* reflective
	* shinyness?
	* How to combine colours
	*/

RGBColour::RGBColour()
{
	_red = 0;
	_green = 0;
	_blue = 0;
}

RGBColour::RGBColour(double red, double green, double blue)
{
	_red = red;
	_green = green;
	_blue = blue;
}

RGBColour::~RGBColour()
{

}

double RGBColour::Red()
{
	return _red;
}

double RGBColour::Green()
{
	return _green;
}

double RGBColour::Blue()
{
	return _blue;
}

RGBColour RGBColour::operator*(const RGBColour &rhs)
{
	RGBColour temp;
	temp._red = _red * rhs._red;
	temp._green = _green * rhs._green;
	temp._blue = _blue  * rhs._blue;

	return temp;
}

RGBColour RGBColour::operator+(const RGBColour &rhs)
{
	RGBColour temp;
	temp._red = _red + rhs._red;
	temp._green = _green + rhs._green;
	temp._blue = _blue  + rhs._blue;

	return temp;
}

RGBColour RGBColour::operator*(const double &rhs)
{
	RGBColour temp;
	temp._red = _red * rhs;
	temp._green = _green * rhs;
	temp._blue = _blue  * rhs;

	return temp;
}

RGBColour RGBColour::operator/(const RGBColour &rhs)
{
	RGBColour temp;
	temp._red = _red / rhs._red;
	temp._green = _green / rhs._green;
	temp._blue = _blue  / rhs._blue;

	return temp;
}

RGBColour RGBColour::operator/(const double &rhs)
{
	RGBColour temp;
	temp._red = _red * rhs;
	temp._green = _green * rhs;
	temp._blue = _blue  * rhs;

	return temp;
}

bool RGBColour::operator==(const RGBColour &rhs)
{
	bool equal = false;
	if (_red == rhs._red && _blue == rhs._blue && _green == rhs._green)
	{
		equal = true;
	}

	return equal;
}

RGBApixel RGBColour::GetPixelColour()
{
	RGBApixel pixel;
	pixel.Red = (int)floor(255 * _red);
	pixel.Green = (int)floor(255 * _green);
	pixel.Blue = (int)floor(255 * _blue);
	return pixel;
}
