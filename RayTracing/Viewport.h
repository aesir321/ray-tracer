#ifndef VIEWPORT_H
#define VIEWPORT_H
#include "Ray.h"
#include "Shape.h"

class Viewport
{
 public :
  Viewport();
  Viewport(double width, double height);
  ~Viewport();
  double Intersection(Ray ray, Shape shape);

 private :
  double _width;
  double _height;
  // double _minDistanceToObserver(double intersection1, double intersection2); Not sure if this is needed atm
    
};
#endif
