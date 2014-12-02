#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Sphere.h"
#include "Vector.h"
#include "LightSource.h"
#include "Viewport.h"

class Scene
{
 public :
	  Scene();
	  ~Scene();
	  std::vector<Shape*> sceneObjects;
	  void AddLightSource(LightSource lightSource);
	  void AddObserver(Vector observer); //Not sure if this is necessary.
	  void Populate(Shape *shape);
	  void TraceRays();
	  void AddViewPort(Viewport viewport);

private :
	Viewport _viewport;
	Vector _observer;
	std::vector<LightSource> _lightSources;
};

#endif
