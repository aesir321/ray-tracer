#ifndef VECTOR_H
#define VECTOR_H
class Vector
{
public:
	Vector();
	Vector(double coord1, double coord2, double coord3, bool cartesian);
	~Vector();

	Vector MultiplyScalar(double scalar);
	Vector DivideScalar(double scalar);
	Vector SubtractScalar(double scalar);
	double Magnitude();
	double AngleXAxis();
	Vector RotateVector(double theta);
	double ScalarProduct(Vector vector);
	Vector Vector::operator+(const Vector &vector);
	Vector Vector::operator-(const Vector &vector);
	Vector Vector::operator/(const Vector &vector);
	void Vector::Add(Vector vector);
	void Vector::ConvertCartesianVectorToPolar();
	Vector Vector::ConvertPolarVectorToCartesian();
	double Vector::GetFirstComponent();
	double Vector::GetSecondComponent();
	double Vector::GetThirdComponent();
	bool Vector::IsCartesian();
	void Vector::PrintCoordinates();
	Vector UnitVector();

protected:

	double _coord1;
	double _coord2;
	double _coord3;
	bool _cartesian;
};
#endif
