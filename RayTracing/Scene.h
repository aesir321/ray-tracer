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
	  std::vector<Sphere> sceneObjects;
	  std::vector<LightSource> lightSources;
	  void AddLightSource(Vector lightSource);
	  void AddObserver(Vector observer);
	  void Populate(Sphere sphere);
	  void TraceRays();
	  void AddViewPort(Viewport viewport);

private :
	Viewport _viewport;
	Vector _observer;
};

#endif
