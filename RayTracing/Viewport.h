#ifndef VIEWPORT_H
#define VIEWPORT_H
#include "Ray.h"
#include "Sphere.h"

class Viewport
{
 public :
  Viewport();
  Viewport(double width, double height, double depth);
  ~Viewport();
  double GetDimension(int dimension);
  Vector Centre();
  double Intersection(Ray ray, Sphere sphere); //Does it make sense to go on the shape class?

 private :
  double _width;
  double _height;
  double _depth;
  Vector _centre;
  // double _minDistanceToObserver(double intersection1, double intersection2); Not sure if this is needed atm
    
};
#endif
