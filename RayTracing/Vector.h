#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
public:

	Vector();
	Vector(double coord1, double coord2, double coord3);
	~Vector();

	double Magnitude();
	double ScalarProduct(Vector vector);
	double X();
	double Y();
	double Z();
	Vector UnitVector();

	Vector operator+(const Vector &rhs);
	Vector operator+(const double &rhs);
	Vector operator*(const double &rhs);
	Vector operator-(const Vector &rhs);
	Vector operator-(const double &rhs);
	Vector operator/(const Vector &rhs);
	Vector operator/(const double &rhs);

private:

	double _coord1;
	double _coord2;
	double _coord3;
};
#endif
