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
	  void Populate(Viewport viewport);
	  void TraceRays();
	  void AddViewPort(Viewport viewport);
	  RGBColour TraceRay(Ray ray);
	  int GetIndexOfClosestShape(std::vector<double> intersections);
	  void SetAmbientCoefficient(double ambientCoefficient);

private :

	Viewport _viewport;
	Vector _observer;
	std::vector<LightSource> _lightSources;
	std::vector<Shape*> _sceneObjects;
	RGBColour _backgroundColour;
	double _ambientCoefficient;
	//Used for accuracy calculations to control arthimetic errors in performing calculations with small numbers.  
	//If greater than epsilon point is taken to be the outside of the sphere, if less then the inside.
	const double _epsilon = 0.00000001;

	RGBColour illumination(Ray incidentRay, Shape *closestShape, RGBColour objectColour, Ray ray);
	RGBColour specularReflection(LightSource lightSource, double projectionNormalToSource, Shape *closestShape, Ray incidentRay, Ray rayToSource, Ray ray);
	RGBColour reflectRays(Shape *shape, Ray incidentRay, Ray ray);
};

#endif
