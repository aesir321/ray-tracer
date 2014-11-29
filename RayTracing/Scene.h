#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "Shape.h"
#include "Vector.h"

class Scene
{
 public :
  Scene();
  Scene(std::vector<Shape> shapes);
  ~Scene();
  std::vector<Shape> shapes;
  void CreateLightSource(Vector vector);
  void Populate();
  void TraceRays();
};
#endif
