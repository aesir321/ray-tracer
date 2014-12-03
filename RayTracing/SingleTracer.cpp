#include "SingleTracer.h"

SingleTracer::SingleTracer()
{
}

SingleTracer::SingleTracer(Scene* scene)
{
	_scene = scene;
}

SingleTracer::~SingleTracer()
{
}

double SingleTracer::TraceRay(Ray& ray)
{
	double intersection = _scene->sceneObjects[1]->Intersection(ray);
	double illumination = 0.0;
	if (intersection != -1.0) //There is something to see!
	{	
		Vector intersectingDirection(ray.Direction().UnitVector().MultiplyScalar(intersection));
		Ray incidentRay(ray.Origin(), intersectingDirection);
		Vector surfaceNormal = _scene->sceneObjects[1]->SurfaceNormal(incidentRay);
		Ray reflectedRay = incidentRay.Reflection(surfaceNormal);

		illumination = reflectedRay.Illumination(_scene->LightSources()[1], surfaceNormal);
	}
	return illumination;
}