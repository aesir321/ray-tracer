#include "Vector.h";
#include<cmath>;
#include<iostream>;
/*
This class defines a vector object.  It will accept either cartesian or spherical polar coords specified by a flag variable.
The class will always covert spherical polar into cartesian coords for any internal calculations but the flag is preserved and it will
always return a vector of the same type that was initially created for that instance.
*/
Vector::Vector() //Default
{
	_coord1 = 0.0;
	_coord2 = 0.0;
	_coord3 = 0.0;
	_cartesian = true;
}

Vector::Vector(double coord1, double coord2, double coord3, bool cartesian) //Overloaded
{
	if (!cartesian) // In conversion method? Can you call class method in the constructor?
	{
		_coord1 = coord1 * sin(coord2) * cos(coord3);
		_coord2 = coord1 * sin(coord2) * sin(coord3);
		_coord3 = coord1 * cos(coord2);
	}
	else
	{
		_coord1 = coord1;
		_coord2 = coord2;
		_coord3 = coord3;		
	}
	_cartesian = cartesian;	
}

Vector::~Vector(){} //Destructor

void Vector::ConvertCartesianVectorToPolar()
{
	double r = 0.0;
	double theta = 0.0;
	double phi = 0.0;

	r = Magnitude();

	double temp = _coord3 / r;	
	theta = acos(temp);	
	phi = atan(_coord2 / _coord1);

	_coord1 = r;
	_coord2 = theta;
	_coord3 = phi;
}

Vector Vector::MultiplyScalar(double scalar)
{
	double coord1 = scalar * _coord1;
	double coord2 = scalar * _coord2;
	double coord3 = scalar * _coord3;
	Vector vector(coord1, coord2, coord3, true);
	
	if (!_cartesian)
		vector.ConvertCartesianVectorToPolar();

	return vector;
}

Vector Vector::DivideScalar(double scalar)
{
	double coord1 = _coord1 / scalar;
	double coord2 = _coord2 / scalar;
	double coord3 = _coord3 / scalar;
	Vector vector(coord1, coord2, coord3, true);
	
	if (!_cartesian)
		vector.ConvertCartesianVectorToPolar();

	return vector;
}

double Vector::Magnitude()
{
	return sqrt(pow(_coord1, 2) + pow(_coord2, 2) + pow(_coord3, 2));
}

double Vector::AngleXAxis()
{
	return atan(_coord2 / _coord1);
}

Vector Vector::RotateVector(double theta)
{
	double x = _coord1 * cos(theta) - _coord2 * sin(theta);
	double y = _coord1 * sin(theta) + _coord2 * cos(theta);
	Vector vector(x, y, _coord3, true); // How to rotate (x, y, z)?

	if (!_cartesian)
		vector.ConvertCartesianVectorToPolar();

	return vector;
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
	
	if (!_cartesian)
		temp.ConvertCartesianVectorToPolar();

	return temp;
}

Vector Vector::operator-(const Vector &rhs)
{
	Vector temp;
	temp._coord1 = _coord1 - rhs._coord1;
	temp._coord2 = _coord2 - rhs._coord2;
	temp._coord3 = _coord3 - rhs._coord3;

	if (!_cartesian)
		temp.ConvertCartesianVectorToPolar();

	return temp;
}

void Vector::Add(Vector vector)
{
	_coord1 = _coord1 + vector._coord1;
	_coord2 = _coord2 + vector._coord2;
	_coord3 = _coord3 + vector._coord3;
}

Vector Vector::ConvertPolarVectorToCartesian()
{
	double r = Magnitude();
	double x = r * sin(_coord2) * cos(_coord3);
	double y = r * sin(_coord2) * sin(_coord3);
	double z = r * cos(_coord2);

	Vector vector(x, y, z, true);
	return vector;
}

void Vector::PrintCoordinates()
{
	Vector vector(_coord1, _coord2, _coord3, true);
	if (!_cartesian)
	{
		vector.ConvertCartesianVectorToPolar();
		std::cout << "(" << vector._coord1 << ", " << vector._coord2 << ", " << vector._coord3 << ")" << std::endl;
	}
	else
	{
		std::cout << "(" << _coord1 << ", " << _coord2 << ", " << _coord3 << ")" << std::endl;
	}
}

double Vector::GetFirstComponent()
{
	double x = 0.0;
	if (!_cartesian)
	{
		ConvertCartesianVectorToPolar();
		x = _coord1;
	}
	else
		x = _coord1;

	return x;
}
double Vector::GetSecondComponent()
{
	double y = 0.0;
	if (!_cartesian)
	{
		
		ConvertCartesianVectorToPolar();
		y = _coord2;
	}
	else
		y = _coord2;

	return y;
}
double Vector::GetThirdComponent()
{
	double z = 0.0;
	if (!_cartesian)
	{
		
		ConvertCartesianVectorToPolar();
		z = _coord3;
	}
	else
		z = _coord3;

	return z;
}

bool Vector::IsCartesian()
{
	return _cartesian;
}