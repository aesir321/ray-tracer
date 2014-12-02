#ifndef VIEWPORT_H
#define VIEWPORT_H
#include "Ray.h"
#include "Sphere.h"

class Viewport
{
 public :
  Viewport();
  Viewport(double width, double height, int numberXPixels, int numberYPixels, Vector centre);
  ~Viewport();
  double GetDimension(int dimension);
  int GetNumberOfPixels(int dimension);
  Vector GetPosition();
  Vector Centre();
  double Intersection(Ray ray, Sphere sphere); //Does it make sense to go on the shape class?

 private :
  double _width;
  double _height;
  int _numberXPixels;
  int _numberYPixels;
  Vector _centre;     
};
#endif
