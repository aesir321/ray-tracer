#ifndef SCENE_H
#define SCENE_H

#include "Vector.h"
#include "LightSource.h"
#include "Viewport.h"
#include "Shape.h"
#include "RGBColour.h"

#include <vector>

class Scene
{
 public :
	  Scene();
	  Scene(Viewport viewport, Vector observer, std::vector<LightSource> lightSources, std::vector<Shape*> sceneObjects, RGBColour backgroundColour, double ambientCoefficient);
	  ~Scene();

	  void Populate(Shape* shape);
	  void Populate(LightSource lightSource);
	  void Populate(Vector observer);
	  void TraceRays();
	  void AddViewPort(Viewport viewport);
	  RGBColour TraceRay(Ray ray);
	  int GetIndexOfClosestShape(std::vector<double> intersections);

private :

	Viewport _viewport;
	Vector _observer;
	std::vector<LightSource> _lightSources;
	std::vector<Shape*> _sceneObjects;
	RGBColour _backgroundColour;
	double _ambientCoefficient;

	RGBColour illumination(Ray incidentRay, Shape *closestShape, RGBColour finalColour, RGBColour objectColour);
	RGBColour specularReflection(RGBColour finalColour, RGBColour objectColour, LightSource lightSource, double projectionNormalToSource, Shape *closestShape, Ray incidentRay, Ray rayToSource);
};

#endif
