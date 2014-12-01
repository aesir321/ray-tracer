#ifndef RAY_H
#define RAY_H

#include "Vector.h"
#include "LightSource.h"

class Ray : public Vector
{
 public :
  Ray();
  Ray(double coord1, double coord2, double coord3, bool cartesian);
  ~Ray();
  Ray Reflection(Vector surfaceNormal);
  Ray Refraction();
  double Illumination(Ray ray, LightSource lightSource, Vector surfaceNormal); //Check what value would be
  Vector Direction();

};
#endif
