#include "Vector.h"
#include<cmath>

Vector::Vector()
{
	_coord1 = 0.0;
	_coord2 = 0.0;
	_coord3 = 0.0;
}

Vector::Vector(double coord1, double coord2, double coord3)
{
	_coord1 = coord1;
	_coord2 = coord2;
	_coord3 = coord3;		
}

Vector::~Vector()
{

}

double Vector::Magnitude()
{
	return sqrt(pow(_coord1, 2) + pow(_coord2, 2) + pow(_coord3, 2));
}

double Vector::ScalarProduct(Vector vector)
{
	return _coord1 * vector._coord1 + _coord2 * vector._coord2 + _coord3 * vector._coord3;
}

Vector Vector::operator+(const Vector &rhs)
{
	Vector temp;

	temp._coord1 = _coord1 + rhs._coord1;
	temp._coord2 = _coord2 + rhs._coord2;
	temp._coord3 = _coord3 + rhs._coord3;

	return temp;
}

Vector Vector::operator+(const double &rhs)
{
	Vector temp;

	temp._coord1 = _coord1 + rhs;
	temp._coord2 = _coord2 + rhs;
	temp._coord3 = _coord3 + rhs;

	return temp;
}

Vector Vector::operator*(const double &rhs)
{
	Vector temp;
	temp._coord1 = _coord1 * rhs;
	temp._coord2 = _coord2 * rhs;
	temp._coord3 = _coord3 * rhs;

	return temp;
}

Vector Vector::operator-(const Vector &rhs)
{
	Vector temp;

	temp._coord1 = _coord1 - rhs._coord1;
	temp._coord2 = _coord2 - rhs._coord2;
	temp._coord3 = _coord3 - rhs._coord3;

	return temp;
}

Vector Vector::operator-(const double &rhs)
{
	Vector temp;

	temp._coord1 = _coord1 - rhs;
	temp._coord2 = _coord2 - rhs;
	temp._coord3 = _coord3 - rhs;

	return temp;
}

Vector Vector::operator/(const Vector &rhs)
{
	Vector temp;

	temp._coord1 = _coord1 / rhs._coord1;
	temp._coord2 = _coord2 / rhs._coord2;
	temp._coord3 = _coord3 / rhs._coord3;

	return temp;
}

Vector Vector::operator/(const double &rhs)
{
	Vector temp;

	temp._coord1 = _coord1 / rhs;
	temp._coord2 = _coord2 / rhs;
	temp._coord3 = _coord3 / rhs;

	return temp;
}

double Vector::X()
{
	return _coord1;
}

double Vector::Y()
{
	return _coord2;
}

double Vector::Z()
{
	return _coord3;
}

Vector Vector::UnitVector()
{
	Vector temp(_coord1, _coord2, _coord3);
	return temp / temp.Magnitude();
}