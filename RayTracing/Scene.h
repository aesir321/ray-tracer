#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Vector.h"
#include "LightSource.h"
#include "Viewport.h"
#include "Shape.h"
#include "RGBColour.h"





class Scene
{
 public :
	  Scene();
	  ~Scene();
	  void AddLightSource(LightSource lightSource);
	  void AddObserver(Vector observer);
	  void Populate(Shape* shape);
	  void TraceRays();
	  void AddViewPort(Viewport viewport);
	  std::vector<LightSource> LightSources();
	  RGBColour TraceRay(Ray ray);
	  std::vector<Shape*> sceneObjects;
	  int GetIndexOfClosestShape(std::vector<double> intersections);

private :
	Viewport _viewport;
	Vector _observer;
	std::vector<LightSource> _lightSources;
};

#endif
