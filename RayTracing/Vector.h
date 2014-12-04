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
	Vector operator+(const Vector &vector);
	Vector operator*(const double &scalar);
	Vector operator-(const Vector &vector);
	Vector operator/(const Vector &vector);
	void Add(Vector vector);
	void ConvertCartesianVectorToPolar();
	Vector ConvertPolarVectorToCartesian();
	double GetFirstComponent();
	double GetSecondComponent();
	double GetThirdComponent();
	bool IsCartesian();
	void PrintCoordinates();
	Vector UnitVector();

protected:

	double _coord1;
	double _coord2;
	double _coord3;
	bool _cartesian;
};
#endif
