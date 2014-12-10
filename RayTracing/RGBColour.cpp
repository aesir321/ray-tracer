#include "RGBColour.h"
#include <algorithm>

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

RGBColour RGBColour::operator+(const double &rhs)
{
	RGBColour temp;
	temp._red = _red + rhs;
	temp._green = _green + rhs;
	temp._blue = _blue + rhs;

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
	temp._red = _red / rhs;
	temp._green = _green / rhs;
	temp._blue = _blue  / rhs;

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

RGBApixel RGBColour::Normalise()
{
	double light = _red + _green + _blue;
	double rgbOverflow = light - (255 * 3);

	if (rgbOverflow > 0)
	{
		_red = _red + rgbOverflow * _red / light;
		_green = _green + rgbOverflow * _green / light;
		_blue = _blue + rgbOverflow * _blue / light;
	}

	_red = (int)floor(std::max(0.0, std::min(_red, 255.0)));
	_green = (int)floor(std::max(0.0, std::min(_green, 255.0)));
	_blue = (int)floor(std::max(0.0, std::min(_blue, 255.0)));

	RGBApixel pixel;

	pixel.Red = (ebmpBYTE)_red;
	pixel.Green = (ebmpBYTE)_green;
	pixel.Blue = (ebmpBYTE)_blue;

	return pixel;
}
