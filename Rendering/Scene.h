#ifndef SCENE_H
#define SCENE_H

#include "../Geometry/Vector.h"
#include "../Geometry/LightSource.h"
#include "Viewport.h"
#include "../Geometry/Shape.h"
#include "RGBColour.h"

#include <vector>

class Scene
{
public:

	Scene();
	Scene(Viewport viewport, Vector observer, std::vector<LightSource> lightSources, std::vector<Shape*> sceneObjects, RGBColour backgroundColour, double ambientCoefficient);
	~Scene();

	void Populate(Shape* shape);
	void Populate(LightSource lightSource);
	void Populate(Vector observer);
	void Populate(Viewport viewport);
	void TraceRays(const char *filename);
	RGBColour TraceRay(Ray ray);
	void SetAmbientCoefficient(double ambientCoefficient);

private:

	Viewport _viewport;
	Vector _observer;
	std::vector<LightSource> _lightSources;
	std::vector<Shape*> _sceneObjects;
	RGBColour _backgroundColour;
	double _ambientCoefficient;
	//Used for accuracy calculations to control arthimetic errors in performing calculations with small numbers.  
	//If greater than epsilon point is taken to be the outside of the sphere, if less then the inside.
	const double _epsilon = 0.0000001;
	const int _maxDepth = 3; //Do not want to recurse indefinitely!

	RGBColour illumination(Ray incidentRay, Shape *closestShape, RGBColour objectColour, Ray ray);
	RGBColour specularReflection(LightSource lightSource, double projectionNormalToSource, Shape *closestShape, Ray incidentRay, Ray rayToSource, Ray ray);
	RGBColour reflectRays(Shape *shape, Ray incidentRay, int depth);
	int getIndexOfClosestShape(std::vector<double> intersections);

};

#endif
