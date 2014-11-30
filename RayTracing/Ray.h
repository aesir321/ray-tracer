#ifndef RAY_H
#define RAY_H
#include "Vector.h"

class Ray : public Vector
{
 public :
  Ray();
  Ray(double coord1, double coord2, double coord3, bool cartesian);
  ~Ray();
  Ray Reflection();
  Ray Refraction();
  double Illumination(); //Check what value would be
  Vector Direction();

 private :
  double _x0;
  double _y0;
  double _z0;
};
#endif
